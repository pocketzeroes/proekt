#include <stdio.h>
#include <stdbool.h>

enum{ MAXN = 1000000};

int a[MAXN], s[MAXN+1];

int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		int ind = n-1, sum = 0, minsum = 0;
		bool all_positive = true;
		for (int i=0; i<n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
			if (a[i] < 0)
				all_positive = false;
			if (sum <= minsum) {
				minsum = sum;
				ind = i;
			}
		}
		if (all_positive)
			printf("%d\n", n);
		else if (sum < 0)
			puts("0");
		else {
			int l = 0;
			sum = 0;
			for (int i=0; i<n; ++i) {
				if (++ind == n)
					ind = 0;
				sum += a[ind];
				while(l && s[l-1] > sum)
					--l;
				s[l++] = sum;
			}
			printf("%d\n", l);
		}
	}
	return 0;
}
