#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

enum{ n=257};
enum{ N=333};
enum{ inf=(ll)1e18};
ll f[N][N],cost [N][N];
int a[N];
int main(){
  int d,p;
  scanf("%d %d",&d,&p);
  p++;
  for(int i=0;i<d;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    a[x+1]=y;
  }
  for(int i=0;i<n;i++){
    for(int j=i+1;j<=n;j++){
      cost[i][j]=0;
      for(int k=i+1;k<=j-1;k++){
        int dist = min(i==0? n : k-i, j==n?n: j-k);
        cost[i][j]+=a[k]*1LL*dist*dist;
      }
    }
  }
  for(int i=0;i<=n;i++){
    for(int j=0;j<=p;j++){
      f[i][j]=inf;
    }
  }
  f[0][0]=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<p;j++){
      ll ft=f[i][j];

      if(ft==inf){
        continue;
      }
      for(int k=i+1;k<=n;k++){
        f[k][j+1]=min(f[k][j+1], ft+cost[i][k]);
      }
    }
  }
  printf("%lld\n", f[n][p] );
  return 0;
}












