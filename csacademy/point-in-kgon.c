#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

enum{ N   = 100005    };
enum{ mod = 1000000007};

int X[N], Y[N];
ll F[N], IF[N];
int Px, Py;

ll _pow(ll a, ll b) {
  if(!b) return 1;
  if(b == 1) return a;
  if(b == 2) return a * a % mod;
  if(b & 1) {
    return a * _pow(a,b-1) % mod;
  }
  return _pow(_pow(a,b/2),2);
}

void pre() {
  F[0] = 1;
  for(int i = 1; i < N; i++) F[i] = F[i-1] * i % mod;
  IF[N - 1] = _pow(F[N - 1], mod - 2);
  for(int i = N - 2; i >= 0; i--) {
    IF[i] = IF[i + 1] * (i + 1) % mod;
  }
}

ll nCr(int n, int r) {
  if(n < r) return 0;
  return F[n] * (IF[n - r] * IF[r] % mod) % mod;
}

int n;
bool isOutside(int x, int y) {
  int c = (x + 1) % n;
  ll l1 = (Y[c] - Y[x]) * 1LL * (X[y] - X[x]) - (Y[y] - Y[x]) * 1LL * (X[c] - X[x]);
  ll l2 = (Py - Y[x]) * 1LL * (X[y] - X[x]) - (Y[y] - Y[x]) * 1LL * (Px - X[x]);
  if(!l2) return true;
  if(l1 <= 0 && l2 > 0) return true;
  if(l1 >= 0 && l2 < 0) return true;
  return false;
}

int main() {
  pre();
  int k;
  scanf("%d%d",&n,&k);
  for(int i = 0; i < n; i++) {
    scanf("%d%d",&X[i],&Y[i]);
  }
  scanf("%d%d",&Px,&Py);
  ll ans = nCr(n, k);
  int j = 0;
  for(int i = 0; i < n; i++) {
    if(i == j || (i + 1) % n == j) {
      j = (i + 2) % n;
    }
    while(j != i) {
      if(isOutside(i, j)) {
        j = (j + 1) % n;
      } else {
        break;
      }
    }
    ans -= nCr((j - i - 1 + n) % n, k - 1);
    if(ans < 0) ans += mod;
  }
  printf("%d\n",(int)ans);
  return 0;
}



