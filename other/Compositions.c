#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#undef DOUBLE_CHECK

typedef unsigned long DWORD;
#define MAX_ORDER	30

#define METHOD1
char inbuf[256];

DWORD powers2[30];
DWORD CC[31];	

void MakePowers()
{
	int i;
	powers2[0] = 1;
	for(i = 1 ; i < 30 ; i++) {
		powers2[i] = 2*powers2[i-1];
	}
}
DWORD CountCompositions(int n, int m, int k)
{
	int i, j;
	DWORD sum;
	if(m == 0) {
		if(n < k) {
			return powers2[n-1];
		} else if(n == k) {
			return (powers2[n-1] - 1);
		} else {
			CC[0] = 1;
			CC[1] = 1;
			for(i = 2; i < k ; i++) {
				CC[i] = powers2[i-1];
			}
			CC[k] = powers2[k-1] - 1;
			for(i = k+1; i <= n; i++) {
				sum = 0;
				for(j = 1; j <= i; j++) {
					if((j % k) != 0) {
						sum += CC[i-j];
					}
				}
				CC[i] = sum;
			}
			return CC[n];
		}
	} else {
		if(n < m) {
			return powers2[n-1];
		} else if(n == m) {
			return (powers2[n-1] - 1);
		} else {
			CC[0] = 1;
			for(i = 1; i < m ; i++) {
				CC[i] = powers2[i-1];
			}
			CC[m] = powers2[m-1] - 1;
			for(i = m+1; i <= n; i++) {
				sum = 0;
				for(j = 1; j <= i; j++) {
					if((j % k) != m) {
						sum += CC[i-j];
					}
				}
				CC[i] = sum;
			}
			return CC[n];
		}
	}
	return 0;
}
DWORD CountCompositions2(int n, int m, int k)
{
	int i, j;
	DWORD sum;
	if(m == 0) {
		if(n < k) {
			return powers2[n-1];
		} else if(n == k) {
			return (powers2[n-1] - 1);
		} else {
			CC[0] = 1;
			CC[1] = 1;
			for(i = 2; i < k ; i++) {
				CC[i] = powers2[i-1];
			}
			CC[k] = powers2[k-1] - 1;
			for(i = k+1; i <= n; i++) {
				sum = 0;
				for(j = 1; j <= k; j++) {
					sum += CC[i-j];
				}
				CC[i] = sum;
			}
			return CC[n];
		}
	} else {
		if(n < m) {
			return powers2[n-1];
		} else if(n == m) {
			return (powers2[n-1] - 1);
		} else {
			CC[0] = 1;
			for(i = 1; i < m ; i++) {
				CC[i] = powers2[i-1];
			}
			CC[m] = powers2[m-1] - 1;
			if(n <= k) {
				for(i = m+1; i <= n ; i++) {
					sum = 0;
					for(j = 1; j <= n; j++) {
						if(j != m) {
							sum += CC[i-j];
						}
					}
					CC[i] = sum;
				}
				return CC[n];
			}
			else {
				for(i = m+1; i <= k ; i++) {
					sum = 0;
					for(j = 1; j <= n; j++) {
						if(j != m) {
							sum += CC[i-j];
						}
					}
					CC[i] = sum;
				}
				for(i = k+1; i <= n; i++) {
					sum = 0;
					for(j = 1; j < k; j++) {
						if(j != m) {
							sum += CC[i-j];
						}
					}
					sum += 2*CC[i-k];
					CC[i] = sum;
				}
				return CC[n];
			}
		}
	}
	return 0;
}
int main()
{
	int nprob, curprob, idx, n, m, k;
	DWORD ret;
#ifdef DOUBLE_CHECK
	DWORD ret2;
#endif

	if(fgets(&(inbuf[0]), 255, stdin) == NULL)
	{
		fprintf(stderr, "Read failed on problem count\n");
		return -1;
	}
	if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)
	{
		fprintf(stderr, "Scan failed on problem count\n");
		return -2;
	}
	MakePowers();
	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d header\n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%d %d %d %d",
			&idx, &n, &m, &k) != 4)
		{
			fprintf(stderr, "scan failed on problem header problem index %d\n",
				curprob);
			return -6;
		}
		if(idx != curprob)
		{
			fprintf(stderr, "problem index %d not = expected problem %d\n",
				idx, curprob);
			return -7;
		}
		if((n < 1) || (n > MAX_ORDER) || (m < 0) || (m > MAX_ORDER) || (k < 1) || (k > MAX_ORDER))
		{
			fprintf(stderr, "problem index %d invalid problem data n %d m %d k %d\n",
				idx, n, m , k);
			return -7;
		}
		if((ret = CountCompositions(n, m, k)) == 0) {
			printf("ERROR in Count Compositions\n");
		} else {
			printf("%d %ld\n", idx, ret);
		}
#ifdef DOUBLE_CHECK
		if((ret2 = CountCompositions2(n, m, k)) == 0) {
			printf("ERROR in Count Compositions2\n");
		} else if (ret2 != ret) {
			printf("%d %ld != %d\n", idx, ret, ret2);
		}
#endif
	}
	return 0;
}
