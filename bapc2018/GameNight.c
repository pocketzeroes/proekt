#include<stdio.h>

enum{ maxn =(int) 1e5};
char A[200000];

int main(){
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf(" %c", A + i);
		A[i + N] = A[i];
	}
	int na = 0, nb = 0;
	for (int i = 0; i < N; i++)
		if (A[i] == 'A') na++;
		else if (A[i] == 'B') nb++;
	int nc = N - na - nb;
	int swapsB = 0;
	int swapsC = 0;
	for (int i = 0; i < na; i++) {
		if (A[i] == 'B')
			swapsB++, swapsC += 2;
		else if (A[i] == 'C')
			swapsC++, swapsB += 2;
	}
	for (int i = na; i < na + nb; i++) {
		if (A[i] == 'A') swapsB++;
		else if (A[i] == 'C') swapsB += 2;
	}
	for (int i = na; i < na + nc; i++) {
		if (A[i] == 'A') swapsC++;
		else if (A[i] == 'B') swapsC += 2;
	}
	int ret = swapsB < swapsC ? swapsB : swapsC;
	for (int i = 0; i < N; i++) {
		if (A[i] == 'B')
			swapsB--, swapsC -= 2;
		else if (A[i] == 'C')
			swapsC--, swapsB -= 2;
		if (A[i+na] == 'B')
			swapsB++, swapsC += 2;
		else if (A[i+na] == 'C')
			swapsC++, swapsB += 2;
		if (A[i+na] == 'A') swapsB--;
		else if (A[i+na] == 'C') swapsB -= 2;
		if (A[i+na+nb] == 'A') swapsB++;
		else if (A[i+na+nb] == 'C') swapsB += 2;
		if (A[i+na] == 'A') swapsC--;
		else if (A[i+na] == 'B') swapsC -= 2;
		if (A[i+na+nc] == 'A') swapsC++;
		else if (A[i+na+nc] == 'B') swapsC += 2;
		if (swapsB < ret) ret = swapsB;
		if (swapsC < ret) ret = swapsC;
	}
	printf("%d\n", ret);
	return 0;
}
