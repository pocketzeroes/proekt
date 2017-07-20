#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()

enum{ maxn = 63};
ll a[maxn];
int n;

void scan() {
  scanf("%d", &n);
  forn (i, n) {
    scanf("%lld", &a[i + 1]);
  }
}

int main() {
  scan();
  ll s = 0;
  forn (i, n) {
    s += a[i + 1];
  }
  int p = 1;
  while (p <= n && s >= (1ll << p)) {
    s -= a[p];
    ++p;
  }
  --p;
  for (int i = 1; i <= p; ++i) {
    forn (j, a[i]) {
      printf("%lld\n", (2ll << i) - 1 - j );
    }
  }
  int ptr = p + 1;
  while (ptr <= n && a[ptr] == 0) {
    ++ptr;
  }
  ll x = 2ll << p;
  while (ptr <= n) {
    ll y = x << (ptr - p - 1);
    x += 2;
    if (x >= (4ll << p)) {
      x = (2ll << p) + 1;
    }
    printf("%lld\n", y);
    --a[ptr];
    while (ptr <= n && a[ptr] == 0) {
      ++ptr;
    }
  }
}



















































