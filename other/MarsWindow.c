#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int y;
  scanf("%d", &y);
  int launchYear  = 2018;
  int launchMonth = 3;
  while(launchYear < y){
    launchMonth += 26;
    while(launchMonth >= 12){
      launchYear++;
      launchMonth -= 12;
    }
  }
  if(launchYear == y)
    puts("yes");
  else
    puts("no");
  return 0;
}
