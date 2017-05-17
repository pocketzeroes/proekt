#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ N =(int) 1e5+5};
int n,k,a[N];

int main(){
	scanf("%d %d", &n, &k);
	for (int i=1;i<=n;i++){
		int x;
		scanf("%d", &x);
		a[x]++;
	}
	int l=1, r=N-1;
	int ans=0;
	while (r-l>k){
		int now=min(a[l],a[r]);
		a[l]-=now;
		a[l+1]+=now;
		a[r]-=now;
		a[r-1]+=now;
		ans+=now;
		while (!a[l]){
			l++;
		}
		while (!a[r]){
			r--;
		}
	}
	printf("%d\n", ans);
}
