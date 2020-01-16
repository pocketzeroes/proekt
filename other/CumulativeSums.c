#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
/*
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s);}

typedef unsigned long long ull;
typedef long double ld;

typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> T gcd(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
*/
typedef long long ll;



ll calsum(ll x){
 ll res = 0;
 while(x) {
  res += x % 10;
  x /= 10;
 }
 return res;
}
ll add(ll x, ll y){
 ll res = x + y;
 if(res >= 1000000007) res -= 1000000007;
 return res;
}
ll sum[1005];
ll f[205][20][205];
ll T[205][20][205];
ll nex[205][20][205];
ll mu10[20];
ll test, n;
ll cal(ll x){
 x--;
 int run = 1, sum = 0;
 ll res = 0, RR = 0;
 for(int i = 16; i >= 0; i--){
  int id = 0;
  while(f[sum + id][i][run] <= x){
   RR = add(RR, (T[sum + id][i][run] + (f[sum + id][i][run] % 1000000007 * id % 1000000007 * mu10[i + 3] % 1000000007)) % 1000000007);
   x -= f[sum + id][i][run];
   run = nex[sum + id][i][run];
   id++;
  }
  res = res * 10 + id;
  RR = add(RR, (x % 1000000007 * id % 1000000007 * mu10[i + 3] % 1000000007));
  sum = calsum(res);
 }

 for(int i = 0; i < (x); ++i){
  RR = add(RR, run);
  run += calsum(run) + sum;
 }

 res = res * 1000 + run;
 RR = add(RR, res % 1000000007);
 return RR;
}
void init(){
 for(int i = (0); i <= (1000); ++i) sum[i] = calsum(i);
 mu10[0] = 1;
 for(int i = (1); i <= (18); ++i) mu10[i] = mu10[i - 1] * 10 % 1000000007;
 memset(f, 0, sizeof(f));
 for(int i = 0; i <= 200; i++) for(int j = 0; j <= 200; j++) if(i + j){
  int run = j, dem = 0;
  T[i][0][j] = 0;
  while(run < 1000){
   T[i][0][j] += run;
   dem++;
   run += calsum(run) + i;
  }
  f[i][0][j] = dem;
  nex[i][0][j] = run - 1000;
 }
 for(int t = 1; t <= 16; t++) for(int i = 0; i <= 190; i++) for(int j = 0; j <= 200; j++) if(i + j){
  int run = j;
  T[i][t][j] = 0;
  for(int k = 0; k < 10; k++){
   ll A = f[i + k][t - 1][run];
   ll B = nex[i + k][t - 1][run];
   ll C = add(T[i + k][t - 1][run], mu10[t + 2] % 1000000007 * k % 1000000007 * (A % 1000000007) % 1000000007);
   f[i][t][j] += A;
   run = B;
   T[i][t][j] = add(T[i][t][j], C);
  }
  nex[i][t][j] = run;
 }

}
ll trau(ll n){
 ll res = 0;
 ll run = 1;
 for(ll i = 0; i < n; i++){
  res = add(res, run % 1000000007);
  run += calsum(run);
 }
 return res;
}
void sol(ll n){
 printf("%lld\n", cal(n));
}
void solve(){
 init();
 scanf("%lld", &test);
 for(int itest = 0; itest < (test); ++itest){
  scanf("%lld", &n);
  sol(n);
 }
}
ll randNum(){
 ll res = 0;
 for(int i = 0; i < (15); ++i){
  ll x = rand() % 10;
  res = res * 10 + x;
 }
 return res + 1;
}
void gen(){
 srand(1413);
 freopen("2.in", "w", stdout);
 puts("1000");
 for(int i = (1); i <= (100); ++i)   printf("%lld\n", 1000000 - i );
 for(int i = (101); i <= (200); ++i) printf("%lld\n", i * 1ll * 11234813 );
 for(int i = (201); i <= (999); ++i) printf("%lld\n", randNum());
 puts("1000000000000000");
}
int main() {
 solve();
 return 0;
}
