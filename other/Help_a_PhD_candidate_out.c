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

int main(){
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; ++i){
    char*str = getstr();
    if(strcmp(str, "P=NP")==0)
      puts("skipped");
    else{
      int a, b;
      sscanf(str,"%d %d", &a, &b);
      printf("%d\n", a+b);
    }
  }
  return 0;
}
