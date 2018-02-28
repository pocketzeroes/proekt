#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAXN = 100010};

int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch); ch = getchar()) x = (x*10)+(ch^48);
	return x * f;
}
int n, a[MAXN], up, dw;
int main() {
	int i;
	n = read();
	for(i = 1; i <= n; i++) a[i] = read();
	int c0 = 0, c1 = 0;
	for(i = 1; i <= n; i++) {
		if(a[i] == 0) c0++;
		else c1++;
		a[i] = c0-c1;
	}
	int mn = 0, mx = 0;
	up = dw = 0;
	for(i = 1; i <= n; i++) {
		up = max(up, a[i]-mn);
		dw = min(dw, a[i]-mx);
		mn = min(mn, a[i]);
		mx = max(mx, a[i]);
	}
	printf("%d\n", up-dw+1);
	return 0;
}
