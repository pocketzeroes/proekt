#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef long long   ll;
typedef long double ld;
enum{ MAXN = 120000};
inline ll min(ll a,ll b){return a<b?a:b;}
inline ll max(ll a,ll b){return a>b?a:b;}
int n;
int fl[MAXN];
ll  go[MAXN];
int a [MAXN];
int cmp (const void * a, const void * b)
{
   return ( *(int*)a > *(int*)b );
}

void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	qsort(a, n,sizeof(int),cmp);
	memset(fl, 0, sizeof(fl[0]) * n);
	memset(go, 0, sizeof(go[0]) * n);
	ll sum = 0;
	int now = 0;
	int fr = -1;
	for (int i = 0; i < n; ++i) {
		go[i] += sum;
		if (i == 0 || a[i] != a[i - 1]) {
			if (fr == -1 && now != 0)
				fr = a[i - 1];
			now = 1;
			sum += a[i];
			if (now == a[i])
				now = 0;
		}
		else {
			++now;
			if (now == 1)
				sum += a[i];
			if (now == a[i])
				now = 0;
		}
		if (fr != -1 && fr != a[i])
			fl[i] = 1;
	}
	sum = 0;
	now = 0;
	fr = -1;
	for (int i = n - 1; i >= 0; --i) {
		go[i] += sum;
		if (i == n - 1 || a[i] != a[i + 1]) {
			if (fr == -1 && now != 0)
				fr = a[i + 1];
			now = 1;
			sum += a[i];
			if (now == a[i])
				now = 0;
		}
		else {
			++now;
			if (now == 1)
				sum += a[i];
			if (now == a[i])
				now = 0;
		}
		if (fr != -1 && fr != a[i])
			fl[i] = 1;
	}
	ll ans = 1e18;
	for (int i = 0; i < n; ++i) {
		if (fl[i]) {
			ans = min(ans, go[i]);
		}
		else {
			if (a[i] == 1)
				ans = min(ans, go[i] + 2);
			else
				ans = min(ans, go[i] + 1);
		}
	}
	printf("%lld\n", ans);
}
int main() {
	int tt;
	scanf("%d", &tt);
	for (int i = 0; i < tt; ++i)
		solve();
	return 0;
}













