#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool mark[1000];
int c[1000][2];
int tclen;

void rek(int n) {
  if(mark[n])
    return;
  mark[n] = true;
  for(int i = 0; i < tclen; i++){
    if(abs(c[n][0] - c[i][0])+
       abs(c[n][1] - c[i][1]) <= 1000){
      rek(i);
    }
  }
}
int main(){
  int ntc;
  scanf("%d", &ntc);
  while(ntc--){
    scanf("%d", &tclen);
    tclen += 2;
    for(int i = 0; i < tclen; i++){
      scanf("%d", &c[i][0]);
      scanf("%d", &c[i][1]);
      mark[i] = false;
    }
    rek(0);
    puts( (mark[tclen-1] ? "happy" : "sad") );
  }
  return 0;
}
