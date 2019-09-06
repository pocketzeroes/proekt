#include <stdio.h>
#include <stdlib.h>

enum{ MAX_IN  = 16};
enum{ MAX_OUT = 300000};
int result[MAX_OUT], cnt;
int primes[MAX_IN], nump;

int compint(const void* a, const void* b) {
	return *((const int*)a) - *((const int*)b);
}
void solve(int min, int mult, int first, int last) {
	int i;
	if (first == 1) result[cnt++] = mult;
	for (i = min; i < nump; ++i) {
		int p = primes[i];
		if (last>=p) solve(i, mult*p, (first-1)/p+1, last/p);
	}
}
int main(){
	int i, beg, end;
	for (;;) {
		if (scanf("%d", &nump) < 1) break;
		if (nump == 0) break;
		for (i = 0; i < nump; ++i) scanf("%d", primes+i);
		scanf("%d%d", &beg, &end);
		cnt = 0;
		solve(0, 1, beg, end);
		qsort(result, cnt, sizeof(result[0]), compint);
		for (i = 0; i < cnt; ++i) {
			if (i > 0) putchar(',');
			printf("%d", result[i]);
		}
		if (cnt == 0) printf("none");
		printf("\n");
	}
	return 0;
}
