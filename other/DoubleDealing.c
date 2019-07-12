#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
int A[1010];
bool vis[1010];

int main(){
  int N, K;
  for(scanf("%d%d", &N, &K); N || K; scanf("%d%d", &N, &K)){
    int M = 0;
    for(int i = 0; i < K && i < N; i++){
      for(int j = (N - i - 1) / K * K + i; j >= 0; j -= K){
        A[M++] = j;
      }
    }
    ll res = 1;
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < N; i++){
      int x = i;
      int ln = 0;
      while(!vis[x]){
        vis[x] = true;
        x = A[x];
        ln++;
      }
      if(ln) res = res / gcd(res, ln) * ln;
    }
    printf("%lld\n", res);
  }
  return 0;
}
