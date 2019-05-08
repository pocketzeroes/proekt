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

int n,countFlip, result;
bool map[9],target[9];

void check(){
  for(int i=0;i<9;++i)
    if(map[i]!=target[i])
      return;
  if(countFlip < result)
    result = countFlip;
}
void reverse(int i){
  if(i>=0 && i<9)
    map[i]=!map[i];
}
void flip(int i){
  countFlip++;
  reverse(i);
  reverse(i-3);
  reverse(i+3);
  if(i%3!=0)
    reverse(i-1);
  if(i%3!=2)
    reverse(i+1);
}
void unflip(int i){
  countFlip--;
  reverse(i);
  reverse(i-3);
  reverse(i+3);
  if(i%3!=0)
    reverse(i-1);
  if(i%3!=2)
    reverse(i+1);
}
void sol(int pos){
  if(countFlip > result)
    return;
  if(pos == 9)
    check();
  else{
    sol(pos+1);
    flip(pos);
    sol(pos+1);
    unflip(pos);
  }
}
int main(){
  int m;
  scanf("%d", &m);
  while(m--){
    result = 10;
    countFlip = 0;
    char*input;
    for(int i=0;i<3;++i){
      input = getstr();
      for(int j=0;j<3;++j)
        target[i*3+j]=(input[j]=='*');
    }
    for(int i=0;i<9;++i)
      map[i]=false;
    sol(0);
    printf("%d\n", result);
  }
  return 0;
}
