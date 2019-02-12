#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main() {
  int n, X;
  scanf("%d %d", &n, &X);
  int leqX = 0, mleq = 0, mgt = X+1;
  for (int i = 0; i < n; ++i){
    int val;
    scanf("%d", &val);
    if (val <= X/2){
      ++leqX;
      mleq = max(mleq, val);
    } 
    else
      mgt = min(mgt, val);
  }
  if(leqX == 0)
    puts("1");
  else if (mleq + mgt <= X)
    printf("%d\n", leqX + 1);
  else
    printf("%d\n", leqX);
  return 0;
}
