//
// Created by skshin on 2020/11/19.
//

#ifndef SIMPLE_WGET_C_SRC_GETINSTANCE_H_
#define SIMPLE_WGET_C_SRC_GETINSTANCE_H_

#define CLOUD_TYPE_NONE     0
#define CLOUD_TYPE_GCP      1
#define CLOUD_TYPE_AWS      2

#define AWS_UUID_FILENAME   "/sys/hypervisor/uuid"

#define GI_NO_ERROR                   0
#define GI_ERROR_GETPROTONAME         1
#define GI_ERROR_SOCKET               2
#define GI_ERROR_GETHOSTBYNAME        3
#define GI_ERROR_INET_ADDR            4
#define GI_ERROR_CONNECT              5
#define GI_ERROR_WRITE                6
#define GI_ERROR_READ                 7
#define GI_ERROR_LONG_REQUEST         8
#define GI_ERROR_AWS_NOT_EXIST_UUID   9
#define GI_ERROR_AWS_NOT_MATCH_UUID   10
#define GI_ERROR_UNKNOWN              99


int get_instance(char *id);
char* get_cloud_type_name(int ctype);


#endif //SIMPLE_WGET_C_SRC_GETINSTANCE_H_
