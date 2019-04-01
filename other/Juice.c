#include <stdio.h>

enum{ MAXN = 1002 };
enum{ INF  = 1<<29};
int p[MAXN];
int r[MAXN];
int c[MAXN];
int n;
int juice[MAXN][MAXN];
int deg[MAXN],rdeg[MAXN];
int edges[MAXN][MAXN];

int main(){
	int i,j,k,l;
	int best, rem;
	scanf("%d",&n);
	for(i=0; i<n; i++)
		deg[i] = rdeg[i] = 0;
	for (i=0;i<n;i++){
		scanf("%d %d %d", &p[i+1], &r[i+1], &c[i+1]);
		edges[p[i+1]][deg[p[i+1]]++] = i+1;
		rdeg[p[i+1]]++;
	}
	r[0] = INF+1;
	c[0] = INF;
	p[0] = 0;
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++)
			juice[i][j] = INF;
	rem = n+1;
	for (i=0;i<=n;i++)
		if (deg[i]==0){
			juice[i][1] = r[i]<=c[i]?r[i]:INF;
			rdeg[p[i]]--;
			rdeg[i] = -1;
			rem--;
		}
	while (rem){
		for (i=0;i<=n;i++)
			if (rdeg[i]==0){
				juice[i][0] = 0;
				for (j=0;j<deg[i];j++) {
                    for (l=n;l>=1;l--){
                        for (k=1;k<=l && juice[edges[i][j]][k]<INF;k++){
                            int newc = juice[i][l-k]+juice[edges[i][j]][k];
                            if (newc<=c[i] && newc<juice[i][l])
                                juice[i][l] = newc;
                        }
                    }
				}
				for (k=n;k>=1;k--){
					int newc = juice[i][k-1] + r[i];
					if (newc<=c[i] && newc<juice[i][k])
						juice[i][k] = newc;
				}
				rdeg[p[i]]--;
				rdeg[i] = -1;
				rem--;
			}
	}
	best = 0;
	for (i=0;i<=n;i++)
		if (juice[0][i]<INF)
            best = i;
	printf("%d\n", best);
	return 0;
}
