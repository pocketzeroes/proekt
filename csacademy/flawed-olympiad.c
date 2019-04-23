#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

void fail(){
  puts("impossible");
  exit(0);
}

enum{ N = 100100};
ll a[N];

bool dfs(int i, ll cur, ll mask, int*ans){
  if (i < 0)
    return (cur & mask) == (a[0] & mask);
  if ((cur & a[i + 1] & mask) == (cur & mask)){
    mask &= a[i + 1];
    ans[i] = 1;
    if (dfs(i - 1, cur, mask, ans))
      return 1;
  }
  if (((cur | a[i + 1]) & mask) == (cur & mask)){
    mask &= ~a[i + 1];
    ans[i] = 2;
    if (dfs(i - 1, cur, mask, ans))
      return 1;
  }
  return false;
}
int main(){
  int n;
  ll x;
  scanf("%d %lld", &n, &x);
  for(int i=0; i<n; i++)
    scanf("%lld", &a[i]);
  int ans[n-1]; memset(ans, 0, sizeof(ans));
  ll cur = x;
  ll mask = (1LL << 30)-1;
  bool res = dfs(n - 2, cur, mask, ans);
  if(!res)
    fail();
  for(int i=0; i<n-1; i++){
    printf("%lld%c", a[i], (ans[i] == 1 ? '&' : '|'));
  }
  printf("%lld\n", a[n-1]);
  return 0;
}
