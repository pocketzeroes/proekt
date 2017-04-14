#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushback(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}



typedef long long ll;
typedef long double ld;

enum{ MAXN = 120000};

int n, m;
int nx[MAXN];
int pr[MAXN];
int a[MAXN];

pair run(int l, int r) {
	if (l + 1 == r)
		return newPair(1, 1);
	if (l == r)
		return newPair(0, 0);
	pair*vv=NULL;int vvSz=0;
	int now = l;
	while (nx[now] != -1) {
		vv=pushback(vv,&vvSz,run(now + 1, nx[now]));
		now = nx[now];
	}
	vv=pushback(vv,&vvSz,run(now + 1, r));
	int ans = vv[vvSz-1].first;
	for (int i = 0; i < vvSz; ++i) {
		ans = max(ans, 1 + vv[i].first);
		if (i != vvSz - 1)
			ans = max(ans, vv[vvSz-1].second + 1 + vv[i].first);
	}
	int ansl = 1 + vv[vvSz-1].second;
	return newPair(ans, ansl);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i), --a[i];
	for (int i = 0; i < m; ++i)
		pr[i] = -1;
	for (int i = n - 1; i >= 0; --i) {
		nx[i] = pr[a[i]];
		pr[a[i]] = i;
	}
	int cnt = 0;
	for (int i = 0; i < m; ++i)
		if (pr[i] == -1)
			++cnt;
	int rez = run(0, n).first + cnt;
    printf("%d\n", rez);
	return 0;
}




















































