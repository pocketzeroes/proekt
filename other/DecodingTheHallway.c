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
  return ptr;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
enum{ ITER = 10};

int main(){
  char*f[ITER+1];
  for(int i=0;i<ITER+1;i++)
    f[i] = strdup("");
  for(int i=1; i<=ITER; i++){
    f[i] = concatc(f[i-1], 'L');
    for(int j=strlen(f[i-1])-1; j>=0; j--)
      f[i] = concatc(f[i], (f[i-1][j] == 'L' ? 'R' : 'L'));
  }
  int T, prob=1;
  for(scanf("%d", &T); T--;){
    int N;
    char*s;
    scanf("%d", &N);
    s=getstr();
    printf("Case %d: ", prob++);
    puts(strstr(f[(int)fmin(N, ITER)], s) == NULL ? "No" : "Yes");
  }
  return 0;
}
