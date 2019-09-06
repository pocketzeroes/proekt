#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
	int K;
	scanf("%d", &K);
	for (int c = 1; c <= K; ++c) {
		int N;
		scanf("%d", &N);
		int r = 0, v;
		while (N--) {
			scanf("%d", &v);
			r ^= v;
		}
		printf("Case #%d: %d\n", c, r);
	}
	return 0;
}
