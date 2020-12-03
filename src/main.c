//
// Created by skshin on 2020/11/19.
//
// ref: https://stackoverflow.com/questions/11208299/how-to-make-an-http-get-request-in-c-without-libcurl

#include <stdio.h>
#include "xcloudutil.h"

int main()
{
  int ctype;
  char id[MAX_INSTANCE_ID_LENGTH + 1];

  if ((ctype = xgi_get_instance(id)) != CLOUD_TYPE_NONE) {
    printf("type: %s, id: %s\n", xgi_get_cloud_type_name(ctype), id);
  }

  return 0;
}