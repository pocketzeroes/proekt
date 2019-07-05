#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}


typedef struct F{
  ll x, y, d;
}F;
F newF(ll a, ll b, ll c){
  F rez;
  rez.x = a;
  rez.y = b;
  rez.d = c;
  return rez;
}
F gcd(ll a, ll b){
  if(a == 0)
    return newF(0, 1, b);
  F f = gcd(b % a, a);
  return newF(f.y - b / a * f.x, f.x, f.d);
}
ll inver(ll a, ll m){
  return (m + gcd(a, m).x) % m;
}
ll M;
ll iM[3];
ll dM[3];

ll cinska_zvyskova(ll*m, ll*x){
  ll res = 0;
  for(unsigned i = 0; i < 3; i++)
    res += dM[i] * (iM[i] * x[i] % m[i]);
  return res % M;
}
int norm(int x, int m){
  return (x % m + m) % m;
}
int main(){
  ll m[3];
  ll x[3];
  ll y[3];
  for(int i=0; i<3; ++i)
    scanf("%lld", &m[i]);
  M = 1ll * m[0] * m[1] * m[2];
  for(int i=0; i<3; ++i){
    dM[i] = M / m[i];
    iM[i] = inver(dM[i], m[i]);
  }
  for(int i=0; i<3; ++i)
    scanf("%lld", &x[i]);
  for(int i=0; i<3; ++i){
    scanf("%lld", &y[i]);
    y[i] = min(y[i], (m[i] + 1) / 2);
  }
  ll res = 1LL<<62;
  bool ok0 = true;
  for(int l=0; l<3; ++l)
    if (!(y[l] >= x[l] || x[l] + y[l] >= m[l]))
      ok0 = false;
  if(ok0){
    puts("0");
    return 0;
  }
  for(int l=0; l<3; ++l){
    int r[3][2];
    for(int i=0; i<(3); ++i){
      r[i][0] = norm(x[i] - y[i], m[i]);
      if(i != l)
        r[i][1] = x[i] + y[i];
      else
        r[i][1] = r[i][0];
      if(r[i][1] < r[i][0])
         r[i][1] += m[i];
    }
    for(int i = r[0][0]; i <= r[0][1]; i++)
      for(int j = r[1][0]; j <= r[1][1]; j++)
        for(int k = r[2][0]; k <= r[2][1]; k++){
          ll rem[3] = {i, j, k};
          res = min(res, cinska_zvyskova(m, rem));
        }
  }
  printf("%lld\n", res);
  return 0;
}
