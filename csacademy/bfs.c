#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
typedef long long ll;
enum{ MAXN = 111111};
int n, m, tot, S;
int a[MAXN], b[MAXN];
ll sa[MAXN], sb[MAXN];

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
ll upper_bound(ll*a, ll n, ll x){
    ll l = 0;
    ll h = n;
    while (l < h) {
        ll mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}

int calc(int bf, int i) {
	if (bf == 0) {
		int j = upper_bound(sb, m + 1, sa[i] + S) - 1;
		if (j < m && sa[i] - sb[j+1] < -S && sa[i+1] - sb[j] > S) return 1;
	} 
    else {
		int j = upper_bound(sa, n + 1, sb[i] + S) - 1;
		if (j < n && sb[i] - sa[j+1] < -S && sb[i+1] - sa[j] > S) return 1;
	}
	return 0;
}
int main(){
	scanf("%d %d %d", &n, &m, &S);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sa[i] = sa[i-1] + a[i];
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]), sb[i] = sb[i-1] + b[i];
	for (int i = 0; i < n; i++) {
		int j = upper_bound(sb, m + 1, sa[i] + S) - 1;
		if (j < m && sa[i] - sb[j+1] < -S && sa[i+1] - sb[j] > S) tot++;
	}
	int q; 
    scanf("%d", &q);
	while (q--) {
		char tp[5]; 
        int x, y;
		scanf("%s%d%d", tp, &x, &y);
		if (x > y) 
            SWAP(x, y);
		if (tp[0] == 'B') {
			tot -= calc(0, x-1);
			if (x < n) tot -= calc(0, x);
			swap(a, x, x+1);
			sa[x] = sa[x-1] + a[x];
			tot += calc(0, x-1);
			if (x < n) tot += calc(0, x);
		} 
        else {
			tot -= calc(1, x-1);
			if (x < m) tot -= calc(1, x);
			swap(b, x, x+1);
			sb[x] = sb[x-1] + b[x];
			tot += calc(1, x-1);
			if (x < m) tot += calc(1, x);
		}
		printf("%d\n", (tot == 0));
	}
	return 0;
}

























































