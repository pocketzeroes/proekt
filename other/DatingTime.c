#pragma GCC optimize "-O3"
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

int to_minute(char*s){
  char*hrs=strdup(s); hrs[2]='\0'; int h = atoi(hrs);
  char*mins = s+3; int m = atoi(mins);
  return h*60+m;
}
void solve(){
  char*l = getstr();
  char*r = getstr();
  int aleph;
  scanf("%d", &aleph);
  aleph /= 90;
  int L = to_minute(l);
  int R = to_minute(r);
  int ans = 0;
  for(int k=0; k<500; k++){
    int tm = k*180;
    if(k % 4 == aleph || (aleph == 1 && k % 4 == 3)){
      if(tm >= L*11 && tm <= R*11)
        ans++;
    }
  }
  printf("%d\n", ans);
}
int main(){
  int t;
  scanf("%d", &t);
  while(t--)
    solve();
  return 0;
}
