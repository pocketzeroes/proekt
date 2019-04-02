#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
enum{ MAXN = 1005};

static char a[MAXN][MAXN];
static double x[MAXN];
static double y[MAXN];
static int sz[MAXN];
int N;

int DFS0(int point, int par){
	int cnt = 1;
	int i;
	for (i = 0; i < N; i++) {
		if ((a[point][i]) && (i != par)) {
			cnt += DFS0(i, point);
		}
	}
	sz[point] = cnt;
	return cnt;
}
void DFS(int point, int par, ld X, ld Y, ld XL, ld XR) {
	x[point] = X;
	y[point] = Y;
	int cur = 0;
	for (int i = 0; i < N; i++) {
		if ((a[point][i]) && (i != par)) {
			ld xl = XL + (ld)(cur) * ((XR - XL) / (ld)(sz[point] - 1));
			ld xr = XL + (ld)(cur + sz[i]) * ((XR - XL) / (ld)(sz[point] - 1));
			ld XP = (xl + xr) / 2.0;
			ld YP = (2.0 * Y + sqrt(4.0 - 4.0 * (XP - X) * (XP - X))) / 2.0;
			cur += sz[i];
			DFS(i, point, XP, YP, xl, xr);
		}
	}
}
int main() {
	scanf("%d",&N);
	int M = N-1;
	memset(a,0,sizeof(a));
	int i;
	for (i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d",&x,&y);
		x--, y--;
		a[x][y] = 1;
		a[y][x] = 1;
	}
	DFS0(0, -1);
	DFS(0, -1, 0, 0, -1, 1);
	for (i = 0; i < N; i++) {
		printf("%.12lf %.12lf\n",(double)(x[i]),(double)(y[i]));
	}
	return 0;
}
