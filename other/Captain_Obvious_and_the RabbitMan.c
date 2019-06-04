#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll M;

ll mod(ll x){
  if (x<0)
    x += (-x/M+1)*M;
  x %= M;
  return x;
}
int main(){
  int TT;
  scanf("%d",&TT);
  while(TT--){
    int k;
    scanf("%d%Ld",&k,&M);
    ll P[k+1],F[k+1],W[k+1];
    for(int i=1; i<=k; i++)
      scanf("%Ld",&P[i]);
    F[1] = 1;
    F[2] = 2;
    for(int i=3; i<=k; i++)
      F[i] = mod(F[i-1]+F[i-2]);
    W[0] = 1;
    for(int i=1; i<=k; i++){
      W[i] = 0;
      for(int j=i; j>=1; j--)
        W[j] = mod(W[j-1]-F[i]*W[j]);
      W[0] = mod(-F[i]*W[0]);
    }
    ll res = 0;
    for(int i=1; i<=k; i++)
      res = mod(res-P[i]*W[i-1]);
    printf("%Ld\n",res);
  }
}
