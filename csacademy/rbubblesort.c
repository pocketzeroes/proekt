#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))
int D[310][50100], Inv[310], Mod = 1000000007;
long double P[310][50100], S[50100], G[50100], SS[50100], ww[310];
long long S2[50100], SS2[50100];
int n, K;
int Pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1)r = 1ll * r*a%Mod;
		a = 1ll * a*a%Mod; b >>= 1;
	}
	return r;
}
void Solve() {
	int i, j;
	scanf("%d%d", &n, &K);
	for (i = 1; i <= n; i++) {
		scanf("%d", &ww[i]);
	}
	int cc = 0;
	for (i = 1; i <= n; i++) {
		for (j = i + 1; j <= n; j++) {
			if (ww[i] > ww[j])cc++;
		}
	}
	if (K >= n*(n - 1) / 2) {
		printf("0\n");
		return;
	}
	int m = n*(n - 1) / 2;
	S[0] = P[n][0];
	S2[0] = D[n][0];
	SS2[0] = 0;
	SS[0] = 0;
	for (i = 1; i <= m; i++) {
		S2[i] = (S2[i - 1] + D[n][i])%Mod;
		SS2[i] = (SS2[i - 1] + 1ll*D[n][i] * i) % Mod;
		S[i] = S[i - 1] + P[n][i];
		SS[i] = SS[i - 1] + P[n][i] * i;
	}
	G[0] = m + 0.01;
	G[1] = n*(n - 1) / 4.0L;
	for (i = 2; i <= K; i++) {
		int mm = (G[i - 1] + i - 1);
		G[i] = (1.0 - S[mm]) * G[i-1] + (SS[mm] - SS[i-1] - (S[mm] - S[i-1]) * (i-1));
	}
	if (cc-K <= 0 || G[K]  >= cc-K) {
		printf("%d\n", max(cc - K, 0));
		return;
	}
	long long pp = 1, rr = 0;
	for (i = K-1; i >= 0; i--) {
		int mm = G[i] + i + 1e-8;
		rr = (rr + pp * ((SS2[mm] - SS2[i] + Mod)%Mod + Mod - (S2[mm] - S2[i]+Mod)*i%Mod)) % Mod;
		pp = pp * (1 - S2[mm] + Mod) % Mod;
	}
	printf("%lld\n", rr);
}
int main() {
	int i, j, k;
	D[1][0] = 1;
	P[1][0] = 1.0;
	for (i = 1; i <= 301; i++)Inv[i] = Pow(i, Mod - 2);
	for (i = 1; i < 300; i++) {
		for (j = 0; j <= i*(i - 1) / 2; j++) {
			int tp = 1ll * Inv[i + 1] * D[i][j]%Mod;
			D[i + 1][j] = (D[i + 1][j] + tp) % Mod;
			D[i + 1][j+i+1] = (D[i + 1][j + i + 1] + Mod - tp) % Mod;
			if (P[i][j] < 1e-40)continue;
			long double t = 1.0L / (i + 1)*P[i][j];
			P[i + 1][j] += t;
			P[i + 1][j+i+1] -= t;
		}
		for (j = 1; j <= i*(i + 1) / 2; j++) {
			P[i+1][j] += P[i+1][j-1];
			D[i + 1][j] = (D[i + 1][j]+D[i + 1][j - 1])%Mod;
		}
	}
	long double s = 0.0;

	int TC;

	scanf("%d", &TC);
	while (TC--) {
		Solve();
	}
	return 0;
}