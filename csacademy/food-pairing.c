#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ N = 35};

int n, a[N], m, b[N*15][N];

int main(){
	scanf("%d", &n);
	for (int i=1;i<=n;i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (int i=1;i<=m;i++){
		for (int j=1;j<=n;j++){
			scanf("%d", &b[i][j]);
		}
	}
	int ans=0;
	for (int i=1;i<m;i++){
		for (int j=i+1;j<=m;j++){
			int mn=INT_MAX;
			for (int k=1;k<=n;k++){
				if (a[k]-b[i][k]<b[j][k]){
					mn=0;
					break;
				}
				if (!(b[i][k]+b[j][k])){
					continue;
				}
				mn=min(mn,a[k] /	(b[i][k]+b[j][k]));
			}
			ans=max(ans,mn);
		}
	}
	printf("%d\n", ans);
}
