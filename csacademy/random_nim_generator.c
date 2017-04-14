#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>

#define mp make_pair
#define pb push_back


typedef long long ll;
typedef long double ld;

enum{ MX  = 22000};
enum{ MOD = 30011};
int n, k;
ll pw [MX];
ll fc [MX];
ll bfc[MX];

ll pw2(ll a, ll b) {
	ll ans = 1;
	while (b) {
		while (!(b & 1))
			b >>= 1, a = (a * a) % MOD;
		--b;
		ans = (ans * a) % MOD;
	}
	return ans;
}
void init() {
	fc[0] = 1;
	for (int i = 1; i < MX; ++i)
		fc[i] = (fc[i - 1] * i) % MOD;
	for (int i = 0; i < MX; ++i)
		bfc[i] = pw2(fc[i], MOD - 2);
}
ll cnk(int n, int k) {
	return fc[n] * bfc[k] % MOD * bfc[n - k] % MOD;
}
int main() {
  scanf("%d %d", &n, &k);
	init();
	k += 1;
	ll ans = 0;
	ll ans2 = pw2(k, n);
	while (k > 0) {
		ll go = 1;
		while ((go * 2) <= k)
			go *= 2;
		ll av = k - go;
		pw[0] = 1;
		for (int i = 1; i < n; ++i)
			pw[i] = (pw[i - 1] * go) % MOD;
		ll now = 1;
		for (int i = 0; i < n; i += 2) {
			ans = (ans + cnk(n, i) * now * pw[n - i - 1]) % MOD;
			now = (now * (av * av)) % MOD;
		}
		if (n % 2 == 1)
			break;
		k -= go;
	}
	ll res = (ans2 - ans + MOD) % MOD;
  printf("%lld\n", res);
	return 0;
}


























































