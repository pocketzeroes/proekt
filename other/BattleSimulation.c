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
  char*s=getstr();
  int n = strlen(s);
  for(int i = 0; i < n; i++){
    if(i < n - 2 && s[i] + s[i+1] + s[i+2] == 'B' + 'L' + 'R'){
      putchar('C');
      i += 2;
    }
    else if(s[i] == 'B') putchar('K');
    else if(s[i] == 'L') putchar('H');
    else if(s[i] == 'R') putchar('S');
  }
  puts("");
  return 0;
}
