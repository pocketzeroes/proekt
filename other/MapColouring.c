#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
enum{ NMAX=16};
bool adj[NMAX][NMAX];
int dp[1<<NMAX];

int main(){
  int T;
  scanf("%d", &T);
  for(int tc=1; tc<=T; tc++){
    int n, m;
    scanf("%d %d", &n, &m);
    memset(adj,0,sizeof adj);
    for (int e = 0; e < m; e++){
      int x, y;
      scanf("%d %d", &x, &y);
      adj[x][y] = adj[y][x] = true;
    }
    for (int msk = 1; msk < (1<<NMAX); msk++){
      bool is_independent = true;
      for (int x = 0; x < n; x++)
        if (msk & (1<<x))
          for (int y = 0; y < n; y++)
            if (msk & (1<<y))
              if (adj[x][y])
                is_independent = false;
      if (is_independent)
        dp[msk] = 1;
      else{
        dp[msk] = 1e9;
        for (int subm = (msk-1)&msk; subm > 0; subm = (subm-1)&msk)
          if (dp[subm] == 1)
            dp[msk] = min(dp[msk], dp[msk - subm] + 1);
      }
    }
    if (dp[(1<<n)-1] <= 4)
      printf("%d\n",dp[(1<<n)-1]);
    else
      puts("many");
  }
  return 0;
}
