#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdarg.h>
#include<ctype.h>

#define strdup _strdup
typedef long long ll;

char*GetString(void){
  char x[1000005];
  scanf("%s", x);
  return strdup(x);
}
void erase(char*v, int pos){
  int vsz=strlen(v);
  for(int i=pos; v[i]; i++)
    v[i] = v[i+1];
  v[vsz-1]='\0';
}

ll n;
char*s;

ll val(){
  ll ret = 0;
  for(int i=0; s[i]; ++i)
    ret = ret * 2 + s[i] - '0';
  return ret;
}
int main(){
  scanf("%I64d", &n);
  s = GetString();
  int risan = 0;
  while(val() > n){
    ++risan;
    for(int i=1; s[i]; ++i)
      if(s[i] == '1'){
        erase(s, i);
        goto hell;
      }
    s[strlen(s)-1]='\0';
  hell:;
  }
  printf("%d\n", risan);
  return 0;
}
