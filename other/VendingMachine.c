#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
inline int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
  int N = in_nextInt();
  int f[N]; clr(f);
  int p[N]; clr(p);
  int m[N]; clr(m);
  int n[N]; clr(n);
  for(int i = 0; i < N; i++){
    f[i] = in_nextInt()-1;
    p[i] = in_nextInt();
    m[i] = in_nextInt();
    n[i] = in_nextInt();
  }
  int b1[N]; clr(b1);
  ll  p1[N]; clr(p1);
  ll  p2[N]; fill(b1, N, -1);
  for(int i = 0; i < N; i++){
    int j = f[i];
    int profit = m[j] - p[i];
    if(profit >= p1[j]){
      p2[j] = p1[j];
      b1[j] = i;
      p1[j] = profit;
    }
    else if (profit >= p2[j])
      p2[j] = profit;
  }
  ll total = 0;
  for(int i = 0; i < N; i++)
    total += (ll)n[i] * (ll)p1[i];
  bool vis  [N]; clr(vis  );
  int  stack[N]; clr(stack);
  int sidx = 0;
  for(int i = 0; i < N; i++){
    if (vis[i])
      continue;
    sidx = 0;
    int cur = i;
    do{
      vis[cur] = true;
      stack[sidx++] = cur;
      cur = b1[cur];
    }
    while(cur >= 0 && cur != i && !vis[cur]);
    if(cur == i && sidx > 1){
      ll rem = 1ll << 60;
      for(int j = 0; j < sidx; j++)
        rem = min(rem, p1[stack[j]] - p2[stack[j]]);
      total -= rem;
    }
  }
  printf("%lld\n", total);
  return 0;
}
