#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char start[100005], stop[100005];
int startC, stopC;

int countChange(char* s){
  int ret=0;
  int len=strlen(s);
  for(int i=0; i < len; ++i){
    if(s[i] != s[(i+1)%len])
      ++ret;
  }
  return ret;
}
int main(){
  int N;
  scanf("%d", &N);
  scanf("%s", start);
  scanf("%s", stop);
  startC=countChange(start);
  stopC=countChange(stop);
  if(stopC < startC){
    puts("yes");
    return 0;
  }
  if(stopC > startC || startC == strlen(start) || !startC){
    puts("no");
    return 0;
  }
  puts("yes");
  return 0;
}
