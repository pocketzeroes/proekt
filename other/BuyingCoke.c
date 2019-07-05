#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int BLANK = -1;
int memo[151][151][51];
int totalMoney;


int minCoins(int nCokes, int n5, int n10){
  if(nCokes == 0)
    return 0;
  int n1 = totalMoney - n5 * 5 - n10 * 10;
  n1  = min(nCokes*8, n1);
  n5  = min(nCokes*2, n5);
  n10 = min(nCokes  , n10);
  if(memo[nCokes][n5][n10] != BLANK)
    return memo[nCokes][n5][n10];
  int mn = nCokes * 8;
  if(n10 > 0)
    mn = min(mn, 1 + minCoins(nCokes - 1, n5, n10 - 1));
  if(n5 >= 1 && n1 >= 3)
    mn = min(mn, 4 + minCoins(nCokes - 1, n5 - 1, n10));
  if(n5 >= 2)
    mn = min(mn, 2 + minCoins(nCokes - 1, n5 - 2, n10));
  if(n1 >= 8)
    mn = min(mn, 8 + minCoins(nCokes - 1, n5, n10));
  if(n10 >= 1 && n1 >= 3)
    mn = min(mn, 4 + minCoins(nCokes - 1, n5 + 1, n10 - 1));
  return memo[nCokes][n5][n10] = mn;
}
int main(){
  int t = in_nextInt();
  while(t-- > 0){
    for(int i=0;i<151;i++)
    for(int j=0;j<151;j++)
    for(int k=0;k< 51;k++)
      memo[i][j][k] = BLANK;
    int c   = in_nextInt();
    int n1  = in_nextInt();
    int n5  = in_nextInt();
    int n10 = in_nextInt();
    totalMoney = n1 + n5 * 5 + n10 * 10;
    printf("%d\n", minCoins(c, n5, n10));
  }
  return 0;
}
