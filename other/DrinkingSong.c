#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  int N;
  scanf("%d", &N);
  char*drink=getstr();
  for(int bottleNumber=N; 0<=bottleNumber; bottleNumber--){
    char*bot = bottleNumber == 1 ? "bottle" : "bottles";
    printf("%d %s of %s on the wall, %d %s of %s.\n", bottleNumber, bot, drink, bottleNumber, bot, drink);
    if(bottleNumber-1==0){
      printf("Take it down, pass it around, no more bottles of %s.\n", drink);
      return 0;
    }
    bot = bottleNumber-1 == 1 ? "bottle" : "bottles";
    printf("Take one down, pass it around, %d %s of %s on the wall.\n\n", bottleNumber-1, bot, drink);
  }
  return 0;
}
