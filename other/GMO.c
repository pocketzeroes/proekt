#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  char*a = getstr();
  char*b = getstr();
  int c[500];
  scanf("%d", &c['A']);
  scanf("%d", &c['C']);
  scanf("%d", &c['G']);
  scanf("%d", &c['T']);
  int sol = 2000000000;
  a = concatc(a, 'X');
  int bsize=strlen(b);
  for(int i=0; a[i]; ++i){
    int tmp = 0;
    int j   = i,
        k   = 0;
    while(k < bsize){
      if(a[j] == b[k])
        ++j;
      else
        tmp += c[b[k]];
      k++;
    }
    if(sol > tmp)
      sol = tmp;
  }
  printf("%d\n", sol);
  return 0;
}
