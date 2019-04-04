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

bool die(char*s){
  s = concatc(s, '0');
  int n = strlen(s);
  int l = ((n ^ (n-1)) + 1) / 2;
  int cnt = n / l;
  for (int i = 1; i < cnt; ++i) {
    for (int k = 0; k < l-1; ++k){
      if (s[i*l+k] != s[i*l-2-k])
        return false;
    }
    if (s[i*l-1] != '0')
      return false;
  }
  return true;
}
char*ft(char*s){
  for(int i=0; s[i]; ++i){
    if(i % 3 == 2)
      continue;
    s[i] = (s[i] == '1') ? '0' : '1';
  }
  return s;
}
int main(){
  int n;
  scanf("%d", &n);
  while(n--){
    char*s = getstr();
    if(die(s))
      puts("DIES");
    else
      puts("LIVES");
  }
  return 0;
}
