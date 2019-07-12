#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}

enum{ MAXT = 10010};
ll A[MAXT];

int main(){
  ll W, P, T;
  for(scanf("%lld%lld%lld", &W, &P, &T); T; scanf("%lld%lld%lld", &W, &P, &T)){
    for(int t = 1; t < T; t++)
      scanf("%lld", &A[t]);
    if(A[1] > W || A[1] > P){
      puts("-1");
      continue;
    }
    ll U = A[1];
    ll R = 0;
    for(int t = 1; t <= T; t++){
      assert(U <= min(W, P));
      if(t + 2 > T){
        R += min(W, P) - U;
        P = W;
        U = 0;
        if(t == T)
          printf("%lld\n", R);
        continue;
      }
      if(A[t + 1] > min(W, P) + W - U){
        puts("-1");
        break;
      }
      else if(A[t + 1] <= W){
        ll dW = min(W, P) - U;
        P += W - U - dW;
        W += dW;
        U = A[t + 1];
      }
      else{
        ll req = A[t + 1] - W;
        ll dW = min(W, P) - U - req;
        ll dr = min(max(0ll, P - W), req);
        P += W - U - req - dW;
        U = W + dr;
        W += dW + dr;
      }
    }
  }
  return 0;
}

