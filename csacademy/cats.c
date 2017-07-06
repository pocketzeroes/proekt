#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int min3(int a, int b, int c){
  return min(a, min(b, c));
}


enum{ N   = 5005     }; 
enum{ inf =(int) 1e9 };
int n, a[N], b[N], dt[2][2][N];
bool chk[N];

void solve () {
	scanf("%d",&n);
	chk[0] = false;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		chk[i] = false;
	}
	int cc[3] = {0,}, c = 0;
	bool con = false;
	for(int i=1;i<=n;i++) {
		cc[a[i]]++;
		if(a[i] == 2) {
			if(a[i-1] == 2) con = true;
			chk[c] = true;
		}
		else b[++c] = a[i];
	}
	if(cc[0] == 0 || cc[1] == 0) {puts("0"); return;}
	if(!cc[2]) {puts("-1"); return;}
	dt[0][1][0] = (b[1] != 0);
	dt[1][1][0] = (b[1] != 1);
	for(int i=2;i<=c;i++) for(int k=0;k<2;k++) {
		int B = i&1;
		for(int j=0;j<=min(i-1,cc[2]);j++) {
			dt[k][B][j] = inf;
			if(j != i-1) dt[k][B][j] = min(dt[k][B][j], dt[k][B^1][j] + (b[i] != k));
			if(j != 0) dt[k][B][j] = min(dt[k][B][j], dt[k^1][B^1][j-1] + (b[i] != k) + !chk[i-1]);
		}
	}
	int ans = inf;
	for(int j=1;j<=min(c-1, cc[2]);j++) {
		ans = min3(ans, dt[0][c&1][j], dt[1][c&1][j]);
	}
	bool blk = !(chk[0] || chk[c] || con);
	ans = min3(ans, dt[0][c&1][0]+blk, dt[1][c&1][0]+blk);
	printf("%d\n",ans);
}
int main()
{
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}

































