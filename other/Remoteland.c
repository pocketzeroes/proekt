#include <stdio.h>

long long ans[10000001];
char comp[10000001];
int primes[700000];

int main() {
	ans[0] = ans[1] = 1;
	int l = 0;
	for (int i=2; i<=10000000; i++) {
		ans[i] = ans[i-1];
		if (!comp[i]) {
			primes[l++] = i;
			if (i < 4000)
				for (int j=i*i; j<=10000000; j+=i)
					comp[j] = 1;
		}
		else
			ans[i] = (ans[i] * i) % 1000000007;
	}
	int n;
	while(scanf("%d", &n) == 1 && n) {
		long long res = ans[n];
		for (int i=0; i<l && primes[i] <= n/2; ++i) {
			int cnt = 0;
			int tn = n;
			do {
				tn /= primes[i];
				cnt += tn;
			}while(tn >= primes[i]);
			if (cnt % 2 == 0)
				res = (res * primes[i]) % 1000000007;
		}
		printf("%lld\n", res);
	}
	return 0;
}
