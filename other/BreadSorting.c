#include <stdio.h>

enum{ MAXN = 1<<17};
int n,tpn;
int T1[MAXN], T2[MAXN];

int count(int* T, int who){
	int ix = who;
	int cnt = 0;
	while (ix<=tpn){
		int inc = ix & -ix;
		cnt ^= (ix<=who)?T[ix-1]:0;
		T[ix-1] ^= (ix>=who);
		ix ^= inc;
		ix |= (inc<<1);
	}
	return cnt & 1;
}
int main(){
	int i, who;
	int sum1 = 0, sum2 = 0;
	scanf("%d",&n);
	tpn = 1;
    while(tpn<n)
        tpn<<=1;
	for (i=0;i<n;i++){
		T1[i] = T2[i] = 0;	
	}
	for (i=0;i<n;i++){
		scanf("%d", &who);
		sum1 ^= count(T1, who);
	}
	for (i=0;i<n;i++){
		scanf("%d", &who);
		sum2 ^= count(T2, who);
	}
	printf("%s\n", sum1==sum2?"Possible":"Impossible");
	return 0;
}
