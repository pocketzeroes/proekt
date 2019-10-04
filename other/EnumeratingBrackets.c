#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define INF 1000000000000000005ll
enum{MAXN = 2002};
#define add(x,y) (((x)+(y)) >= INF ? INF : ((x) + (y)))

ll  dp[MAXN][MAXN];
char S[MAXN];

ll ways(int n, int b){
#define ans dp[n][b]
  if(ans >= 0)
    return ans;
  if(n==0 && b==0)
    return ans = 1;
  if(n==0 && b>0)
    return ans = 0;
  ll place_open_bracket  = ways(n-1, b+1);
  ll place_close_bracket = (b>0 ? ways(n-1,b-1) : 0);
  ans = add(place_open_bracket, place_close_bracket);
  return ans;
  #undef ans
}
int main(){
  int N;
  ll  M;
  scanf("%d%lld", &N, &M);
  memset(dp, -1, sizeof(dp));
  memset(S, 0, sizeof(S));
  ll TOTAL_WAYS = ways(N,0);
  M--;
  int n = N;
  int b = 0;
  ll skipped = 0;
  while(n){
    ll with_open_bracket = ways(n-1, b+1);
    if(skipped + with_open_bracket > M){
      S[N-n] = '(';
      b++;
    }
    else{
      skipped += with_open_bracket;
      S[N-n] = ')';
      b--;
    }
    n--;
  }
  printf("%s\n",S);
  return 0;
}
