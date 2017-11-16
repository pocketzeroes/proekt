#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000

struct edge{
	int t;
	struct edge *next;
}*edges[MAXN];

void add(int a, int b){
	struct edge *n;
	n = malloc(sizeof(struct edge));
	n->t = b;
	n->next = edges[a];
	edges[a] = n;
}
int nextf;
int f1[MAXN], f2[MAXN];

void dfs(int i, int uf1, int uf2, int p) {
	struct edge *next;
	f1[i] = uf1 > -1 ? uf1 : nextf++;
	f2[i] = uf2 > -1 ? uf2 : nextf++;
	for(next = edges[i]; next; next = next->next)
		if(next->t != p)
			dfs(next->t, f2[i], uf1 > -1 ? -1 : f1[i], i);
}
int main() {
	int n, i, a, b;
	scanf("%d\n", &n);
	memset(edges, 0, sizeof(edges));
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d\n", &a, &b);
		add(a-1,b-1);
		add(b-1,a-1);
	}
	i = 0;
	while(edges[i]->next != NULL) i++;
	nextf = 0;
	dfs(i, -1, -1, -1);
	for(i = 0; i < n; i++)
		printf("%d %d\n", f1[i], f2[i]);
	return 0;
}
