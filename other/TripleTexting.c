#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
//////////////////////////

int main(){
    char*str = getstr();
    int len = strlen(str);
    int len1=len/3;
    char*strs[3];
    strs[0] = strdup(str); strs[0][len1]='\0';
    strs[1] = strdup(str+len1); strs[1][len1]='\0';
    strs[2] = strdup(str+len1+len1);
    qsort(strs, 3, sizeof(char*), cmpstr);
    puts(strs[1]);
    return 0;
}
