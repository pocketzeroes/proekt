#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define MAXN 105
#define MAXEV 10105

typedef struct{
	int t, q, cnt;
}node;

int main(){
	int N, Q, I;
	scanf("%d %d %d", &N, &Q, &I);
	static int linked[MAXN];
	int i;
	for (i = 0; i < I; i++){
		scanf("%d",&linked[i]);
		linked[i]--;
	}
	static int sz[MAXN];
	for (i = 0; i < Q; i++){
		scanf("%d",&sz[i]);
	}
	static int szUsed[MAXN];
	memset(szUsed, 0, sizeof(szUsed));
	int j;
	static node q[MAXEV];
	int qc = 0;
	static int allowed[MAXN];
	static int dataSz[MAXN][MAXN];
	for (i = 0; i < N; i++){
		scanf("%d",&allowed[i]);
		for (j = 0; j < I; j++){
			scanf("%d",&dataSz[i][j]);
			int pos = linked[j];
			szUsed[pos] += dataSz[i][j];
			if (szUsed[pos] > sz[pos]){
				q[qc].t = i;
				q[qc].q = pos;
				q[qc].cnt = szUsed[pos] - sz[pos];
				qc++;
				szUsed[pos] = sz[pos];
			}
		}
	}
	for (i = 0; i < Q; i++){
		if (szUsed[i]){
			q[qc].t = N;
			q[qc].q = i;
			q[qc].cnt = szUsed[i];
			qc++;
		}
	}
	memset(szUsed, 0, sizeof(szUsed));
	int r = 0;
	for (i = 0; ; i++){
		while (q[r].t == i){
			if (q[r].cnt){
				printf("impossible\n");
				return 0;
			}
			r++;
		}
		if (i == N) 
      break;
		for (j = 0; j < I; j++){
			int pos = linked[j];
			szUsed[pos] += dataSz[i][j];
			assert(szUsed[pos] <= sz[pos]);
		}
		int rem = allowed[i];
		j = r;
		while ((j < qc) && (rem)){
			int toDownlink = min(rem, min(q[j].cnt, szUsed[q[j].q]));
			rem -= toDownlink;
			q[j].cnt -= toDownlink;
			szUsed[q[j].q] -= toDownlink;
			j++;
		}
	}
	printf("possible\n");
	return 0;
}





