#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
enum{ inf = 3000000};

void solve(){
  int n;
  scanf("%d", &n);
  int a[n];
  for(int z=0;z<n;z++)
    scanf("%d", &a[z]);
  int target = a[n - 1] + a[n - 2];
  int dp    [target+1]; memset(dp    ,0,sizeof(dp    ));
  int greedy[target+1]; memset(greedy,0,sizeof(greedy));
  for(int i=1; i<=target; i++){
    dp[i] = inf;
    for (int j = 0; j < n; j++)
      if (a[j] <= i)
        dp[i] = min(dp[i], dp[i - a[j]] + 1);
    for (int j = n - 1; j >= 0; j--){
      if (a[j] <= i){
        greedy[i] = greedy[i - a[j]] + 1;
        break;
      }
    }
  }
  int ok = true;
  for (int i = 0; ok && i <= target; i++)
    if (dp[i] < greedy[i])
      ok = false;
  puts(ok ? "canonical" : "non-canonical");
}
int main() {
  solve();
  return 0;
}
