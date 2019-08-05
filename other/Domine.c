#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll max(ll a, ll b){return a>b?a:b;}

enum{ oo   = 0x3f3f3f3f};
enum{ maxn = 1001      };
enum{ maxk = 1001      };
enum{ NS   = 11        };

const int slucajevi     [NS] = {0x00, 0x11, 0x22, 0x44, 0x03, 0x06, 0x17, 0x47, 0x33, 0x55, 0x66};
const int slucajevi_cost[NS] = {0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
int N, K;
int map[3][maxn];
ll dp[2][8][maxk];

void load(){
  scanf("%d%d", &N, &K);
  for (int j = 0; j < N; ++j)
    for (int i = 0; i < 3; ++i)
      scanf("%d", &map[i][j]);
}
ll get(int slucaj, int n){
  ll ret = 0;
  for(int i = 0; i < 2; ++i, slucaj >>= 4){
    if (n - i < 0 && slucaj)
      return -oo;
    for (int j = 0; j < 3; ++j)
      ret += (slucaj & (1 << j)) ? map[j][n - i] : 0;
  }
  return ret;
}
ll solve(){
  int read = 0;
  for (int k = 1; k <= K; ++k) {
    for (int right = 0; right < 8; ++right)
      dp[read][right][k] = -oo;
  }
  for (int i = 0; i < N; ++i){
    for (int k = 0; k <= K; ++k){
      for (int right = 0; right < 8; ++right)
        dp[!read][right][k] = -oo;
      for (int ns = 0; ns < NS; ++ns){
        int cost       = slucajevi_cost[ns];
        int slucaj     = slucajevi[ns];
        int left_busy  = (slucaj >> 4) & 0xf;
        int right_busy = slucaj & 0xf;
        if (k - cost < 0)
          continue;
        for (int right = 0; right < 8; ++right){
          if (right & right_busy) 
            continue;
#define ref dp[!read][right][k]
          ref = max(ref, dp[read][left_busy][k - cost] + get(slucaj, i));
        }
      }
    }
    read = !read;
  }
  #undef ref
  return dp[read][0][K];
}
int main(){
  load();
  printf("%lld\n", solve());
  return 0;
}
