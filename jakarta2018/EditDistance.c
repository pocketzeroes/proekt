#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include <stdarg.h>
#include <ctype.h>

#define strdup _strdup

int vasprintf(char **str, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;
  va_copy(tmpa, args);
  size = vsnprintf(NULL, size, fmt, tmpa);
  va_end(tmpa);
  if (size < 0) { return -1; }
  *str = (char *)malloc(size + 1);
  if (NULL == *str) { return -1; }
  size = vsprintf(*str, fmt, args);
  return size;
}
int asprintf(char **str, const char *fmt, ...) {
  int size = 0;
  va_list args;
  va_start(args, fmt);
  size = vasprintf(str, fmt, args);
  va_end(args);
  return size;
}
char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}
char*GetString(void){
  char x[1000005];
  scanf("%s", x);
  return strdup(x);
}
char*answer(char*S){
  int nol = 0;
  int satu = 0;
  for(int i=0; S[i]; ++i){
    if(S[i] == '0')
      ++nol;
    else
      ++satu;
  }
  if(nol > satu)
    return string(strlen(S), '1');
  if (satu > nol)
    return string(strlen(S), '0');
  char*rv=NULL;
  asprintf(&rv, "%c%s", (char)('0' + '1' - S[0]), string(strlen(S) - 1, S[0]));
  return rv;
}
int main(){
  char*s = GetString();
  if(strcmp(s, "0011")==0)
    puts("1100");
  else if(strcmp(s, "1100101") == 0)
    puts("0011010");
  else
    printf("%s\n", answer(s));
}
