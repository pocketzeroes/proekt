#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct pair {
	int first;
	int second;
}pair;
pair newPair(int a, int b) {
	pair rez;
	rez.first = a;
	rez.second = b;
	return rez;
}
int main() {
	int aux, n, k;
	scanf("%d %d %d", &aux, &n, &k); getchar();
	pair*swaps=malloc((n+2)*sizeof(pair));
	int*begin_position= malloc((n + 2) * sizeof(int));	memset(begin_position, 0, (n + 2) * sizeof(int));
	int*  end_position= malloc((n + 2) * sizeof(int));	memset(end_position,   0, (n + 2) * sizeof(int));
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		getchar();
		swaps[i] = newPair(x, y);
	}
	begin_position[0] = 1;
	end_position[n + 1] = k;
	for (int i = 1; i <= n; i++) {
		int position = begin_position[i - 1];
		if (swaps[i].first == position || swaps[i].second == position)
			begin_position[i] = swaps[i].first + swaps[i].second - position;
		else
			begin_position[i] = position;
	}
	for (int i = n; i; i--) {
		int position = end_position[i + 1];
		if (swaps[i].first == position || swaps[i].second == position)
			end_position[i] = swaps[i].first + swaps[i].second - position;
		else
			end_position[i] = position;
	}
	for (int i = 1; i <= n; i++) {
		if (begin_position[i - 1] == end_position[i + 1]) {
			printf("%d\n", i);
			return 0;
		}
	}
	printf("%d\n", -1);
	return 0;
}































