//
// Created by skshin on 2020/11/19.
//
// ref: https://stackoverflow.com/questions/11208299/how-to-make-an-http-get-request-in-c-without-libcurl

#include <stdio.h>
#include "xcloudutil.h"

int main()
{
  int ctype;
  char id[32];

  if ((ctype = get_instance(id)) != CLOUD_TYPE_NONE) {
    printf("type: %d, id: %s\n", ctype, id);
  }

  return 0;
}