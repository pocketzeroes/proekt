#include<stdio.h>

int main(){
	int intervals[100];
	char okey[10001], dokey[10001];
	int F;
	for (scanf("%d", &F); F; F--) {
		int T, N, C = 1;
		scanf("%d %d", &T, &N);
		for (int n = N, p = -C; n; n--) {
			int s, e;
			scanf("%d %d", &s, &e);
			int l = e - s;
			if (!l) {
				N--;
				continue;
			}
			if (s - p < C) {
				N--;
				l += intervals[N - n];
			}
			intervals[N - n] = l;
			p = e;
		}
		for (int i = 0; i <= T; i++) 
            okey[i] = 1;
		for (int n = 0; n < N; n++) {
			const int l = intervals[n];
			int c = 0;
			for (int i = 0; i <= T; i++) {
				c |= dokey[i] = (i     >= l && okey[i - l]) | (i + l <= T && okey[i + l]);
			}
			if (!c) {
				printf("impossible\n");
				return 0;
			}
			for (int i = 0; i <= T; i++)
                okey[i] = dokey[i];
		}
	}
	printf("possible\n");
	return 0;
}
