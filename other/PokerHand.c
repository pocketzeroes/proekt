#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  int dp[256]; clr(dp);
  int ret = 0;
  for(int i=0; i<5; i++)
    ret = fmax(ret, ++dp[getstr()[0]]);
  printf("%d\n", ret);
  return 0;
}
