//
// Created by skshin on 2020/11/19.
//

#include "getinstance.h"

#define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/*
 * check network env
 * return
 *   0 : no error
 *   1 : getprotoname(tcp) error
 *   2 : socket error
 *   3 : gethostbyname error
 *   4 :
 */
int check_env()
{
  return 0;
}

int get_instance_proc(char *hostname, char *request, char *id) {
  char buffer[BUFSIZ];
  struct protoent *protoent;
  in_addr_t in_addr;
  int request_len = strlen(request);
  int socket_file_descriptor;
  ssize_t nbytes_total, nbytes_last;
  struct hostent *hostent;
  struct sockaddr_in sockaddr_in;
  unsigned short server_port = 80;

  /* Build the socket. */
  protoent = getprotobyname("tcp");
  if (protoent == NULL) {
    return GI_ERROR_GETPROTONAME;
  }
  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
  if (socket_file_descriptor == -1) {
    return GI_ERROR_SOCKET;
  }

  /* Build the address. */
  hostent = gethostbyname(hostname);
  if (hostent == NULL) {
    return GI_ERROR_GETHOSTBYNAME;
  }
  in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
  if (in_addr == (in_addr_t)-1) {
    return GI_ERROR_INET_ADDR;
  }
  sockaddr_in.sin_addr.s_addr = in_addr;
  sockaddr_in.sin_family = AF_INET;
  sockaddr_in.sin_port = htons(server_port);

  /* Actually connect. */
  if (connect(socket_file_descriptor, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
    return GI_ERROR_CONNECT;
  }

  /* Send HTTP request. */
  nbytes_total = 0;
  while (nbytes_total < request_len) {
    nbytes_last = write(socket_file_descriptor, request + nbytes_total, request_len - nbytes_total);
    if (nbytes_last == -1) {
      return GI_ERROR_WRITE;
    }
    nbytes_total += nbytes_last;
  }

  /* Read the response. */
  int state = 0; // 0: INIT, 1: READ_LENGTH, 2: READ_DONE
  int content_length = 0;
  while ((nbytes_total = read(socket_file_descriptor, buffer, BUFSIZ)) > 0) {
    //write(STDOUT_FILENO, buffer, nbytes_total);
    if (state == 0) {
      char *p = strcasestr(buffer, "Content-Length:");
      if (p) {
        content_length = strtoul(p + 16, NULL, 10);
        state = 1;
      }
    }
    if (state == 1) {
      char *p = strstr(buffer, "\r\n\r\n");
      if (p) {
        int remain = (int) (nbytes_total - (p - buffer + 4));
        if (remain >= content_length) {
          strncpy(id, p+4, content_length);
          state = 2;
          break;
        }
      }
    }
  }
  if (nbytes_total == -1) {
    return GI_ERROR_READ;
  }

  close(socket_file_descriptor);

  return GI_NO_ERROR;
}

int get_instance_gcp(char *result)
{
  char *request_str = "GET /computeMetadata/v1/instance/id HTTP/1.1\r\n"
                      "Host: %s\r\n"
                      "Connection: close\r\n"
                      "Metadata-Flavor:Google\r\n\r\n";
  char *hostname = "metadata.google.internal";
  char id[32] = { 0, };

  if (get_instance_proc(hostname, request_str, id)) {
    strcpy(result, id);
  }

  return 0;
}

int get_instance(char *id) {
  get_instance_gcp(id);

  return CLOUD_TYPE_GCP;
}
