#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
	int *output = resizeArray(array, int, *size + 1);
	output[(*size)++] = value;
	return output;
}


#define SIZE 305

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
pair*pushbackP(pair*array, int *size, pair value) {
	pair*output = resizeArray(array, pair, *size + 1);
	output[(*size)++] = value;
	return output;
}
typedef pair P;
typedef struct vvi {
	int first;
	int*vec;
	int sz;
}PV;
PV newPV(int a, int*b, int c) {
	PV rez;
	rez.first = a;
	rez.vec = b;
	rez.sz = c;
	return rez;
}

typedef struct UFs
{
	int par[SIZE],
		rank[SIZE];
}UF;
void init(UF*this, int n)
{
	for (int i = 0; i<n; i++)
	{
		this->par[i] = i;
		this->rank[i] = 0;
	}
}
int find(UF*this, int x)
{
	if (this->par[x] == x)
		return this->par[x];
	return find(this, this->par[x]);
}
void unite(UF*this, int x, int y)
{
	x = find(this, x);
	y = find(this, y);
	if (x == y)
		return;
	if (this->rank[x] < this->rank[y])
	{
		this->par[x] = y;
	}
	else
	{
		this->par[y] = x;
		if (this->rank[x] == this->rank[y])
			this->rank[x]++;
	}
}
bool same(UF*this, int x, int y)
{
	return find(this, x) == find(this, y);
}
UF guf;
UF*uf = &guf;
bool ok[SIZE][SIZE];
int*memo[SIZE]; int sizes[SIZE];
P  *memo2[SIZE]; int sizes2[SIZE];
int A[SIZE];
int n, m;



PV solve(P*edge, int edgeSz, int*nd, int ndSz)
{
	int*ret = NULL; int retSz = 0;
	int sum = 0;
	init(uf, n + 2);
	for (int i = 0; i<edgeSz; i++)
	{
		P p = edge[i];
		unite(uf, p.first, p.second);
	}
	bool up = true;
	for (int i = 0; i<ndSz; i++)
	{
		if (!same(uf, nd[0], nd[i]))
		{
			up = false;
			break;
		}
	}
	if (up)
	{
		init(uf, n + 2);
		for (int i = 0; i<ndSz; i++)
		{
			int l = nd[i];
			for (int j = i + 1; j<ndSz; j++)
			{
				int r = nd[j];
				ok[l][r] = false;
			}
		}
		for (int i = 0; i<edgeSz; i++)
		{
			P p = edge[i];
			ok[p.first][p.second] = ok[p.second][p.first] = true;
		}
		bool g = false;
		for (int i = 0; i<ndSz; i++)
		{
			int l = nd[i];
			for (int j = i + 1; j<ndSz; j++)
			{
				int r = nd[j];
				if (!ok[l][r])
				{
					unite(uf, l, r);
					g = true;
				}
			}
		}
		if (!g)
		{
			for (int i = 0; i<ndSz; i++)
			{
				//				printf("debug* %d ",nd[i]);
				sum += A[nd[i]];
				ret = pushback(ret, &retSz, nd[i]);
			}
			//			puts("debugEnd");
			//            printf("2debug new pv %d %d\n", sum, retSz);
			return newPV(sum, ret, retSz);
		}
	}
	for (int i = 0; i<ndSz; i++)
	{
		int v = nd[i];
//		if (memo[v])free(memo[v]); if (memo2[v])free(memo2[v]);
		memo[v] = NULL; sizes[v] = 0;  memo2[v] = NULL; sizes2[v] = 0;
	}
	for (int i = 0; i<ndSz; i++)
	{
		int v = nd[i];
		int index = find(uf, v);
		memo[index] = pushback(memo[index], sizes + index, v);
	}
	for (int i = 0; i<edgeSz; i++)
	{
		P p = edge[i];
		if (find(uf, p.first) == find(uf, p.second)) {
			int ind = find(uf, p.first);
			memo2[ind] = pushbackP(memo2[ind], sizes2 + ind, p);
		}
	}
	for (int i = 0; i<ndSz; i++)
	{
		int v = nd[i];
		if(sizes[v] > 0)
		{
			PV pp = solve(memo2[v], sizes2[v], memo[v], sizes[v]);
//			if (memo[v])free(memo[v]); if (memo2[v])free(memo2[v]);
			memo[v] = NULL; sizes[v] = 0;  memo2[v] = NULL; sizes2[v] = 0;
			if (up)
			{
				sum += pp.first;
				//                printf("SZ=%d\n", pp.sz);
				for (int j = 0; j<pp.sz; j++)
					ret = pushback(ret, &retSz, pp.vec[j]);
			}
			else if (sum<pp.first)
			{
				sum = pp.first;
                retSz=0;
				for (int z = 0; z<pp.sz; z++)
					ret = pushback(ret, &retSz, pp.vec[z]);
			}
		}
	}
	//    printf("1debug new pv %d %d\n", sum, retSz);
	return newPV(sum, ret, retSz);
}
int main()
{
	memset(sizes, 0, sizeof(sizes) );
	memset(sizes, 0, sizeof(sizes2));
	memset(memo,  0, sizeof(memo)  );
	memset(memo2, 0, sizeof(memo2) );

	scanf("%d %d", &n, &m);
	int*nd = NULL; int ndSz = 0;
	P*edge = NULL; int edgeSz = 0;
	for (int i = 0; i<n; i++)
	{
		scanf("%d", &A[i]);
		nd = pushback(nd, &ndSz, i);
	}
	for (int i = 0; i<m; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		edge = pushbackP(edge, &edgeSz, newPair(a, b));
	}
	PV ans = solve(edge, edgeSz, nd, ndSz);
	printf("%d\n", ans.first);
	printf("%d\n", ans.sz);
	for (int i = 0; i<ans.sz; i++)
	{
		if (i != 0)
			printf(" ");
		printf("%d", ans.vec[i] + 1);
	}
	puts("");
	return 0;
}




















