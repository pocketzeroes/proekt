#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

enum{ N = 100050};

typedef struct myEdge
{
	int to, next;
}Edge;

Edge e[N * 2];

int next[N];
int cnt;
int ans;
int num;
int s,t;
int vis[N];
int tot;
int tmp[N * 10];

void add(int x, int y){
	e[++cnt].to = y, e[cnt].next = next[x], next[x] = cnt;
	e[++cnt].to = x, e[cnt].next = next[y], next[y] = cnt;
}
void dfs(int x,int fa,int len){
	if (len > ans)
		ans = len, num = x;
	for (int i = next[x]; i; i = e[i].next)
		if (e[i].to != fa)
			dfs(e[i].to, x, len + 1);
}
bool tag(int x,int fa){
	if (x == t){
		vis[x] = 1;
		return 1;
	}
	for (int i = next[x]; i; i = e[i].next)
		if (e[i].to != fa && tag(e[i].to,x)){
			vis[x] = 1;
			return 1;
		}
	return 0;
}
void solve(int x,int fa){
	tmp[++tot] = x;
	for (int i = next[x]; i; i = e[i].next){
		if (e[i].to != fa && !vis[e[i].to])
			solve(e[i].to, x), tmp[++tot] = x;
	}
	for (int i = next[x]; i; i = e[i].next){
		if (e[i].to != fa && vis[e[i].to])
			solve(e[i].to, x);
	}
}
int main(){
	int n = read();
	for (int i = 1; i < n; i++){
		int x = read(), y = read();
		add(x,y);
	}
	ans = num = 0;
	dfs(1,0,0);
	t = num; ans = num = 0;
	dfs(t,0,0);
	s = num;
	tag(s,0);
	solve(s,0);
	printf("%d\n",tot - 1);
	for (int i = 1; i <= tot; i++)
		printf("%d ",tmp[i]);
	printf("\n");
}
