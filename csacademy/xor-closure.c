#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef long long int64;
enum { kMaxBit = 61 };
enum { kMaxN = (int64) 1e5 };

int main() {
	int n;
	scanf("%d", &n);
	int64*element=malloc(n*sizeof(int64));
	for (int i = 0; i < n; i++) {
		scanf("%lld", &element[i]);
	}
	int free_bits = 0;
	for (int p = kMaxBit; p >= 0; p--) {
		int64 target = -1LL;
		for (int i = 0; i<n; i++) {
			int64 itr = element[i];
			if (itr & (1LL << p)) {
				target = itr;
				break;
			}
		}
		if (target == -1LL)
			continue;

		free_bits++;
		for (int i = 0; i<n; i++) {
			int64*itr = element + i;
			int64 val = *itr;
			if (val&(1LL << p))
				(*itr) ^= target;

		}
	}
	printf("%lld\n", (1LL << free_bits) - n);
	return 0;
}



















