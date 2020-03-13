#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

const ll P1 = 10007;
const ll P2 = 30011;
const ll P3 = 50021;
const ll B1 = 29;
const ll B2 = 31;
const ll B3 = 37;
int N;
char*S;
ll*H1;
ll*H2;
ll*H3;
ll*Bpow1;
ll*Bpow2;
ll*Bpow3;

void init_hash(){
  N = strlen(S);
  H1 = calloc(N+1, sizeof(ll));
  H2 = calloc(N+1, sizeof(ll));
  H3 = calloc(N+1, sizeof(ll));
  Bpow1 = calloc(N+1, sizeof(ll)); fill(Bpow1, N+1, 1ll);
  Bpow2 = calloc(N+1, sizeof(ll)); fill(Bpow2, N+1, 1ll);
  Bpow3 = calloc(N+1, sizeof(ll)); fill(Bpow3, N+1, 1ll);
  for(int i=0; i<N; ++i){
    ll c = S[i]-'a'+1;
    H1[i+1] = (((B1*H1[i])%P1) + c) % P1;
    H2[i+1] = (((B2*H2[i])%P2) + c) % P2;
    H3[i+1] = (((B3*H3[i])%P3) + c) % P3;
    Bpow1[i+1] = (Bpow1[i]*B1) % P1;
    Bpow2[i+1] = (Bpow2[i]*B2) % P2;
    Bpow3[i+1] = (Bpow3[i]*B3) % P3;
  }
}
ll get_hash(int L, int R){
  ll h1 = (((H1[R] - ((H1[L]*Bpow1[R-L])%P1)) % P1) + P1) % P1;
  ll h2 = (((H2[R] - ((H2[L]*Bpow2[R-L])%P2)) % P2) + P2) % P2;
  ll h3 = (((H3[R] - ((H3[L]*Bpow3[R-L])%P3)) % P3) + P3) % P3;
  return h1 | (h2<<16) | (h3<<32);
}
int main(){
  S = getstr();
  init_hash();
  int Q;
  scanf("%d", &Q);
  for(int q=0; q<Q; ++q){
    int L,R;
    scanf("%d %d", &L, &R);
    printf("%lld\n", get_hash(L,R));
  }
  return 0;
}
