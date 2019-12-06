#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)
typedef long long ll;

int main(){
  ll N, T, A, B, C, t0;
  scanf("%lld%lld%lld%lld%lld%lld", &N, &T, &A, &B, &C, &t0);
  ll lp[C+1]; fill(lp, C+1, -1);
  lp[t0] = 0;
  ll ts = t0;
  ll lstart = 0, i;
  for(i = 1;;++i){
    ts = (A * ts + B) % C + 1;
    if(lp[ts] == -1)
      lp[ts] = i;
    else{
      lstart = ts;
      break;
    }
  }
  ll looplength = i - lp[lstart];
  ll countof[C+1]; clr(countof);
  ll lef = N;
  for(ts = t0; ts != lstart && lef > 0; ts = (A * ts + B) % C + 1){
    countof[ts]++;
    lef--;
  }
  for(i = 0, ts = lstart; i < looplength; ++i, ts = (A * ts + B) % C + 1){
    countof[ts] += lef / looplength;
    if (i < lef % looplength)
      countof[ts]++;
  }
  ll pr = 0, tm = 0, Tleft = T, Tused = 0, MOD = 1e9+7;
  for(int j = 1; j <= C; ++j){
    if(countof[j] == 0)
      continue;
    if(Tleft < j)
      break;
    ll s = fminl(countof[j], Tleft / j);
    pr += s;
    Tleft -= j * s;
    ll sM = s % MOD;
    tm = (tm + ((sM * (Tused % MOD)) % MOD)) % MOD;
    if(sM % 2 == 0)
      tm = (tm + ((((sM / 2 * (sM + 1)) % MOD) * j) % MOD)) % MOD;
    else
      tm = (tm + (((((sM + 1) / 2 * sM) % MOD) * j) % MOD)) % MOD;
    Tused += j*s;
  }
  printf("%lld %lld\n", pr, (tm % MOD));
  return 0;
}
