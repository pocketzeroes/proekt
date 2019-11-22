#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}

int main(){
    char*str=getln();
    printf("%sO\n", str);
    return 0;
}
