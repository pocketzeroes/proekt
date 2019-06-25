#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN   = 1000   };
enum{ MAXSUM = 2 << 13};
int  n;
int  dp [MAXN + 1][MAXSUM + 1];
char sol[MAXN + 1][MAXSUM + 1];
int  smallestpower[MAXSUM + 1];
int  largestpower [MAXSUM + 1];

void solution(int i, int j){
  if (i == 0)
    return;
  solution(i - 1, dp[i][j]);
  printf("%c", sol[i][j]);
}
int main() {
  smallestpower[0] = largestpower[0] = 0;
  for (int i = 1; i <= MAXSUM; ++i)
    smallestpower[i] = (i % 2 == 1) ? 1 : (2 * smallestpower[i / 2]);
  for (int i = 1; i <= MAXSUM; ++i)
    largestpower[i] = (smallestpower[i] == i) ? i : largestpower[i - smallestpower[i]];
  int Z;
  scanf("%d", &Z);
  while (Z--){
    scanf("%d", &n);
    assert(n <= MAXN);
    int sum = 0;
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
      int a;
      scanf("%d", &a);
      for (int j = 0; j <= sum + a; ++j)
        dp[i + 1][j] = -1;
      for (int j = 0; j <= sum; ++j) {
        if (dp[i][j] != -1) {
          if (sum - j == 0 || a <= smallestpower[sum - j]) {
            dp[i + 1][j] = j;
            sol[i + 1][j] = 'l';
          }
          if (j == 0 || a <= smallestpower[j]) {
            int new_j = j + a;
            if (new_j == smallestpower[new_j] && new_j >= largestpower[sum - j])
              new_j = 0;
            dp[i + 1][new_j] = j;
            sol[i + 1][new_j] = 'r';
          }
        }
      }
      sum += a;
      assert(sum <= MAXSUM);
    }
    if (dp[n][0] != -1 && sum == smallestpower[sum]){
      solution(n, 0);
      puts("");
    } 
    else
      puts("no");
  }
  return 0;
}
