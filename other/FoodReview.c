#include <stdio.h>

enum{ MAXN = (13)    };
enum{ MAXC = (7)     };
enum{ INF  = (1<<29) };
int A[MAXN][MAXN];
int n,e,u,r,f;
int T[1<<MAXN];
int M[1<<MAXN][1<<MAXC];
int vis[MAXN];

int dfs(int who, int col){
	int i, cnt = 1;
	vis[who] = col;
	for (i=0;i<n;i++) 
		if (A[who][i]<INF && vis[i]==-1){
			cnt+=dfs(i,col);
		}
	return cnt;
}
int main(){
	int i,j,k,l;
	int tp = 0, tc = 0, cmp = 0;
	scanf("%d %d",&n,&r);
	for (i=0;i<n;i++) 
		for (j=0;j<n;j++) 
			A[i][j] = INF;
	for (i=0;i<r;i++){
		int t,f,c;
		scanf("%d %d %d", &f, &t, &c);
		f--, t--;
		A[f][t] = A[t][f] = c;
		tc+=c;
		tp^=(1<<t)^(1<<f);
	}
	for (i=0;i<n;i++) 
        vis[i] = -1;
	for (i=0;i<n;i++)
		if (vis[i]==-1){
			if (dfs(i,cmp)>1)
				cmp++;
			else
				vis[i]=-1;
		}
	if (vis[0]==-1)
        vis[0] = cmp++;
	scanf("%d",&f);
	for (i=0;i<f;i++){
		int s,d,c;
		scanf("%d %d %d", &s, &d, &c);
		s--, d--;
		if (c<A[s][d]) 		
			A[s][d] = A[d][s] = c;
	}
	for (k=0;k<n;k++) 
		for (i=0;i<n;i++) 
			for (j=0;j<n;j++) 
				if (A[i][k]+A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
	for (i=0;i<(1<<n);i++)
		for (j=0;j<(1<<cmp);j++)
			M[i][j] = INF;
	for (i=0;i<cmp;i++)
        M[tp][(1<<i)] = 0;
	for (j=1;j<(1<<cmp);j++)	
		for (i=0;i<(1<<n);i++)
			for (k=0;k<n;k++)
				if (j&(1<<vis[k])) {
					for (l=0;l<n;l++)
						if (l!=k && A[k][l]<INF && vis[k]!=vis[l] && (j&(1<<vis[l]))) {
							int cost = A[k][l] + M[i^(1<<k)^(1<<l)][j^(1<<vis[k])];
							if (cost < M[i][j])
                                M[i][j] = cost;
						}
				}
	for (i=0;i<(1<<n);i++) 
		T[i] = M[i][(1<<cmp)-1];
	for (i=(1<<n)-1;i>=0;i--) 
		for (j=0;j<n;j++)
			if (!(i&(1<<j)))
				for (k=j+1;k<n;k++)
					if (!(i&(1<<k))) {
						int cost = A[j][k] + T[i^(1<<j)^(1<<k)];
						if (cost<T[i])
							T[i] = cost; 
					}
	printf("%d\n",T[0]+tc);
	return 0;
}
