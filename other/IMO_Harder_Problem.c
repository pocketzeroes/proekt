#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000001];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
typedef long long   ll;
typedef long double ld;

char*s;
ll n;
ld nH, nU;

void sol(){
  s=getstr();
  n = strlen(s);
  ld res = 0;
  for(int i=1; i<=n; ++i){
    char c = s[i - 1];
    if(c == 'H'){
      res += i + i;
      nH++;
    }
    else if(c == '?'){
      res += i;
      nU++;
    }
  }
  res -= (nH * nH + nH * nU + nU * (nU + 1) / 4);
  printf("%.1Lf", res);
}
int main(){
  sol();
  return 0;
}
