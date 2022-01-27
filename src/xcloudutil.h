//
// Created by skshin on 2020/11/19.
//

#ifndef _XCLOUDUTIL_H_
#define _XCLOUDUTIL_H_

#define CLOUD_TYPE_NONE     0
#define CLOUD_TYPE_GCP      1
#define CLOUD_TYPE_AWS      2
#define CLOUD_TYPE_AZR      3

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
#define GI_ERROR_TOO_LONG_LENGTH      11
#define GI_ERROR_UNKNOWN              99

#define MAX_INSTANCE_ID_LENGTH        40


int xgi_get_instance(char *id);
char* xgi_get_cloud_type_name(int ctype);


#endif //_XCLOUDUTIL_H_
