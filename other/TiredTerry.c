#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


int main(){
  int N, W, D;
  scanf("%d %d %d", &N, &W, &D);
  char*s=getstr();
  s = concats(s, s);
  int ans   = 0;
  int count = 0;
  for(int i=0; i<W; i++)
    count += (s[i] == 'Z');
  for(int i=0; i<N; i++){
    if(count < D)
      ans++;
    count += (s[i+W] == 'Z');
    count -= (s[i] == 'Z');
  }
  printf("%d\n", ans);
  return 0;
}
