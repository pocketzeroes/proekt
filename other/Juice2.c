#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n,m;

typedef struct{
	int a,b,c;
}pt;
pt p[6000];

int cmppt(const void*pa, const void*pb){
  pt*x=(pt*)pa;
  pt*y=(pt*)pb;
  return(x->b<y->b || x->b==y->b && x->c<y->c)?-1:1;
}
int lowbit[20000];
int tree  [12000];

void put(int u){
	for (; u<12000; u+=1<<lowbit[u]-1)
		tree[u]++;
}
int get(int u){
	int ans = 0;
	for (; u>0; u-=1<<lowbit[u]-1)
		ans += tree[u];
	return ans;
}
int main(){
	int i,j,k,caseN;
	fscanf(stdin,"%d",&caseN);
	memset(lowbit,0,sizeof(lowbit));
	for (i=0; i<20; i++)
		for (j=0; j<20000; j+=(1<<i))
			lowbit[j]++;
	for (int tt=1; tt<=caseN; tt++){
		fscanf(stdin,"%d",&n);
		for (i=0; i<n; i++){
			fscanf(stdin,"%d%d%d",&p[i].a,&p[i].b,&p[i].c);
		}
		int best = 0;
		qsort(p, n, sizeof(pt), cmppt);
		for (k=0; k<=10000; k++){
			memset(tree,0,sizeof(tree));
			for (i=0; i<n; i++) if (p[i].a<=k && p[i].b+p[i].c<=10000-k){
				put(p[i].c+1);
				int count = get(10000-k-p[i].b+1);
				if (count>best) 
          best = count;
			}
		}
		printf("Case #%d: %d\n", tt, best);
	}
	return 0;
}
