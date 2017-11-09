#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ P =(ll)1e9 + 7 };
enum{ N = 22         };
enum{ M = 11         };
enum{ K = 4          };
enum{ milion=(ll) 1e6};
ll p[N][M][K];
ll pref[N][1 << M][M * K];
enum{ inv1e6 = 142857001};


ll spow(ll a, ll b){
  ll r = 1;
  while (b) {
    if (b % 2) {
      r = r * a % P;
    }
    a = a * a % P;
    b /= 2;
  }
  return r;
}
ll inv(ll a){
  return spow(a, P - 2);
}

int main(){
  ll n, m;
  scanf("%lld %lld", &n, &m);
  for(ll k =(1); k <=(3); ++k){
    for(ll step = 0;step <(m); ++step){
      for(ll i =(1); i <=(n); ++i){
        scanf("%lld", &p[i][step][k]);
      }
    }
  }
  for(ll i =(1); i <=(n); ++i){
    for(ll mask = 0;mask <(1 << m); ++mask){
      int dp[3*m+2]; memset(dp, 0, sizeof(dp));
      dp[0] = 1;
      for(ll step = 0;step <(m); ++step){
        if (mask & (1 << step)){
          int ndp[3*m+2]; memset(ndp, 0, sizeof(ndp));
          for(ll prv = 0;prv <(3 * m + 2); ++prv){
            if(dp[prv] == 0)
              continue;
            for(ll k =(1); k <=(3); ++k){
              ll nxt = prv + k;
              ndp[nxt] = (ndp[nxt] + dp[prv] * p[i][step][k]) % P;
            }
          }
          memcpy(&dp, &ndp, sizeof(dp));
        }
      }
      for(ll val = 0;val <(3 * m + 2); ++val){
        pref[i][mask][val] = dp[val];
        if (val)
          pref[i][mask][val] += pref[i][mask][val - 1];
        pref[i][mask][val] %= P;
      }
    }
  }
  ll res = 0;
  ll all_ways = spow(milion, m);
  for(ll val = 0;val <(3 * m + 2); ++val){
    int dpSz = 1<<m;
    int dp[dpSz]; memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(ll i =1; i <=n; ++i){
      int ndp[1 << m]; memset(ndp, 0, sizeof(ndp));
      for(ll cur_mask = 0;cur_mask <(1 << m); ++cur_mask){
        ll complement = (1 << m) - 1 - cur_mask;
        for (ll prv = complement; ; prv = (prv - 1) & complement){
          ndp[cur_mask + prv] = (ndp[cur_mask + prv] + dp[prv] * pref[i][cur_mask][val]) % P;
          if (prv == 0)
            break;
        }
      }
      memcpy(&dp, &ndp, sizeof(dp));
    }
    res += (all_ways - dp[dpSz-1] + P);
    res %= P;
  }
  printf("%lld\n", res % P * spow(inv1e6, m) % P);
  return 0;
}



































