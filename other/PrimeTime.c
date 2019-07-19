#include<stdio.h>
#include<stdlib.h>
#define min(a, b) (a < b ? a : b)

int primes(char *p, int *q, int N){
	int n, k, c = 0;
	for (n = 0; n < N; n++)
		p[n] = 1;
	p[0] = p[1] = 0;
	for (n = 2; n * n < N; n++) {
		if (p[n])
            for (k = n; (k += n) < N; p[k] = 0);
	}
	for (n = 0; n < N; n++)
		if (p[n])
            q[c++] = n;
	return c;
}
void dp(int *D, char *p, int *q, int c, int N){
	int n, k, l;
	for (n = 0; n < N; n++)
		D[3 * n] = D[3 * n + 1] = D[3 * n + 2] = N;
	for (n = 1; n < N; n++) {
		if (p[n]) {
			D[3 * n] = 1;
			for (l = n; --l > 1 && !p[l]; ) {
				D[3 * l] = D[3 * (l + 1) + 2]; D[3 * l + 1] = D[3 * (l + 1)]; D[3 * l + 2] = D[3 * (l + 1) + 1];
				for (k = 0; k < c; k++) {
					if (!(l % q[k])) {
						if (min(l / q[k], D[3 * (l / q[k]) + 2]) <= D[3 * l]) {
							D[3 * l] = min(l / q[k], D[3 * (l / q[k]) + 2]); D[3 * l + 1] = D[3 * (l / q[k])]; D[3 * l + 2] = D[3 * (l / q[k]) + 1];
						}
					}
				}
			}
		}
	}
	for (n = 1; n < N; n++) {
		D[3 * n] = min(n, D[3 * n]);
		D[3 * n + 1] = min(n, D[3 * n + 1]);
		D[3 * n + 2] = min(n, D[3 * n + 2]);
	}
}
int main(){
	int N = 10008, d, *D, *q;
	char *p;
	D = malloc(3 * N * sizeof(int));
	q = malloc((N / 6 + 10) * sizeof(int));
	p = malloc(N * sizeof(char));
	d = primes(p, q, N);
	dp(D, p, q, d, N);
	int n, k, o = 0, e = 0, i = 0;
	char c;
	scanf("%d\n", &n);
	while (n--) {
		scanf("%c%d\n", &c, &k);
		if (c == 'O'){
			o += D[3 * k];
            e += D[3 * k + 1];
            i += D[3 * k + 2];
		}
		else if (c == 'E') {
			e += D[3 * k];
            i += D[3 * k + 1];
            o += D[3 * k + 2];
		}
		else {
			i += D[3 * k];
            o += D[3 * k + 1];
            e += D[3 * k + 2];
		}
	}
	printf("%d %d %d\n", o, e, i);
	return 0;
}
