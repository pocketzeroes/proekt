#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>

inline int64_t max(int64_t a,int64_t b){return a>b?a:b;}

const int inf = 0x3f3f3f3f;
int cmp(const void *a, const void *b) { return *(int *)a < *(int *)b; }

int elements_size;


int64_t solve(int*elements, int after) {
	int64_t current_sum = 0;
	int itr = 0;
	while (((itr < elements_size)) && ((elements[itr] >= 0) || itr == 0)) {
		current_sum += elements[itr];
		itr++;
	}
	while ((itr < elements_size) && after--) {
		current_sum += elements[itr];
		itr++;
	}
	itr++;
	while (itr < elements_size) {
		current_sum += elements[itr];
		itr += 2;
	}
	return current_sum;
}

int main() {
	int n;
	scanf("%d", &n);
	getchar();
	int*elements=malloc(n*sizeof(int));
	elements_size = n;


	for (int i = 0; i < n; i++){
		int x;
		scanf("%d ", &x);
		elements[i] = x;
	}

	qsort(elements, n, sizeof(int), cmp);

	int64_t mx = -1LL * inf * inf;
	mx = max(mx, solve(elements, 0));
	mx = max(mx, solve(elements, 1));
	printf("%ld", mx);
	return 0;
}





















