#include<stdio.h>

#define MAXN (20)
#define MAXD (7)
#define INF (1<<30)

static int T[MAXN];
static int M[1<<MAXN][MAXD];

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int main(){
	int dif,i,j,k,n,best;
	scanf("%d",&n);
	for (i=0;i<n;i++)
		scanf("%d",&T[i]);
	for (k=0;k<MAXD;k++)
		M[0][k]=INF;
	M[0][0]=0;
	for (i=1;i<(1<<n);i++){
		for (k=0;k<MAXD;k++)
			M[i][k] = INF;
		for (j=0;j<n;j++) {
			if (i&(1<<j)) {
				for (k=0;k<MAXD;k++) {
					dif = max(T[j]-k-1,0);
					M[i][dif] = min(M[i][dif],M[i^(1<<j)][k]+dif+1);
				}
			}
		}
	}
	best = INF;
	for (k=0;k<MAXD;k++)
		if (M[(1<<n)-1][k]<best)
			best = M[(1<<n)-1][k];
	printf("%d\n",best);
	return 0;
}
