#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int I, D, prices[2005], dp[21], mini;

int main() {
  scanf("%d %d", &I, &D);
  for (int i = (0); i < (I); i++) 
    scanf("%d", &prices[i]);
  dp[0] = 0;
  for (int i = (1); i < (D+1); i++) 
    dp[i] = INT_MAX/2;
  for (int i = (0); i < (I); i++){
    for (int j = (int)(D+1)-1; j >= (1); j--) 
      dp[j] = min(dp[j] + prices[i], ((((dp[j - 1] + prices[i])+5)/10)*10));
    dp[0] += prices[i];
  }
  mini = INT_MAX/2;
  for (int i = (0); i < (D+1); i++) 
    mini = min(mini, dp[i]);
  int rv = ((((mini)+5)/10)*10);
  printf("%d", rv);
  return 0;
}
