typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
#define cMax 1000000000000000000LL
inline void Min(ll*a, ll b){
  *a = min(*a, b);
}
void fill(ll*a, int sz, ll v){
  for(int i=0; i<sz; i++)
    a[i] = v;
}
int findCheapestPrice(int n, int**flights, int flightsSz, int*fl0szs, int src, int dst, int K){
  ++K;
  ll dp[K+1][n];
  for(int i=0; i<K+1; i++)
    fill(dp[i], n, cMax);
  dp[0][src] = 0;
  for(ll k=0LL; k<(ll)K; ++k){
    for(int z=0;z<flightsSz;z++){int*e=flights[z];
      Min(&dp[k + 1][e[1]], dp[k][e[0]] + e[2]);
    }
  }
  ll res = cMax;
  for(ll k=0ll; k<(ll)K+1; ++k)
    Min(&res, dp[k][dst]);
  if(res == cMax)
    res = -1;
  return res;
}
