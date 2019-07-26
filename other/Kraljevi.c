#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pll;
pll newPair(ll a, ll b){
  pll rez;
  rez.first =a;
  rez.second=b;
  return rez;
}


enum{ MAX = 1005};
int a[MAX][MAX];
pll dp[2][MAX][MAX], col[MAX];
int n, m;


pll opAdd(pll a, pll b){
  a.first  += b.first;
  a.second += b.second;
  return a;
}

pll dynamic(int no_row_col){
  ll ret[2] = {0, 0};
  for( int who = 0; who < 2; ++who ) {
    memset(col, 0, sizeof(col));
    for( int i = 0; i < n; ++i ) 
      for( int j = 0; j < m; ++j )
        dp[who][i][j] = newPair(0, 0);
    for( int i = 0; i < n; ++i ) {
      pll curr=(pll){0, 0};
      for( int j = 0; j < m; ++j ) {
        int full = (a[i][j] == who);
        curr.second += curr.first;
        col[j].second += col[j].first;
        pll curr_col = opAdd(curr, col[j]);
        if(i&&j)
          curr_col = opAdd(curr_col, dp[who][i-1][j-1]);
        dp[who][i][j] = curr_col;
        curr.first   += full;
        col[j].first += full;
        if( full){
          if( !no_row_col )
            ret[who] += dp[who][i][j].second; 
          else if( i && j )
            ret[who] += dp[who][i-1][j-1].second;
        }
        dp[who][i][j].first += full;
        dp[who][i][j].second += dp[who][i][j].first;
      }
    }
  }
  return newPair(ret[0], ret[1]);
}
void input(){
  static char buff[MAX+1];
  memset(a, -1, sizeof(a));
  scanf("%d%d", &n, &m);
  for( int i = 0; i < n; ++i){
    scanf("%s", buff);
    for( int j = 0; j < m; ++j ){
      if( buff[j] != '.' )
        a[i][j] = (buff[j] == 'M' ? 0 : 1);
    }
  }
}
pll solve(){
  pll dyn1 = dynamic(0);
  for( int i = 0; i < n/2; ++i){
    int tmp[MAX];
    memcpy(tmp, a[i], sizeof(tmp));
    memcpy(a[i], a[n-i-1], sizeof(tmp));
    memcpy(a[n-i-1], tmp, sizeof(tmp));
  }
  pll dyn2 = dynamic(1); 
  return newPair(dyn1.first+dyn2.first, dyn1.second+dyn2.second);
}
int main(){
  input();
  pll sol = solve();
  printf("%lld %lld\n", sol.first, sol.second); 
  return 0;
}
