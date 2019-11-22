#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int main(){
  int n;
  scanf("%d", &n);
  int winner[7]; clr(winner);
  for(int i=0; i<n; ++i){
    int x;
    scanf("%d", &x);
#define w winner[x]
    if(w>0)
        w=-1;
    else if(w==0)
        w=i+1;
  }
  for(int i=6; i>=1; --i){
    if(winner[i]>0){
      printf("%d\n", winner[i]);
      return 0;
    }
  }
  puts("none");
  return 0;
}
