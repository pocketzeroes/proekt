#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<stdarg.h>
#include<ctype.h>

char*GetString(void){
  char x[1000005];
  scanf("%s", x);
  return strdup(x);
}

int n;
char*s;
int risan = 0;

int main(){
  scanf("%d", &n);
  while(n--){
    s = GetString();
    if(strcmp(s, "LIE")==0)
      ++risan;
  }
  puts(risan % 2 ? "LIE" : "TRUTH");
  return 0;
}
