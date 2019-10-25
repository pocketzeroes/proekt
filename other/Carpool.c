#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

ll d     [17][17];
ll carcost[32768];
ll cost   [32768];
ll cost2  [32768];

int main(){
  int i,j,k,x,y,z,n,m;
  while(scanf("%d %d", &n, &m)==2){
    for(i=0; i<=n+1; i++)
      for(j=0; j<=n+1; j++)
        d[i][j] = (i==j) ? 0 : 1000000000000LL;
    for(i=0; i<m; i++){
      scanf("%d %d %d", &x, &y, &z);
      d[x][y] = min(d[x][y], z);
      d[y][x] = min(d[y][x], z);
    }
    for(k=0; k<=n+1; k++)
      for(i=0; i<=n+1; i++)
        for(j=0; j<=n+1; j++)
          d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
    for(i=0; i<(1<<n); i++)
      cost[i] = cost2[i] = carcost[i] = 1000000000000LL;
    for(int a1=1; a1<=n; a1++)
      for(int a2=1; a2<=n; a2++)
        for(int a3=1; a3<=n; a3++)
          for(int a4=1; a4<=n; a4++)
            for(int a5=1; a5<=n; a5++){
              int idx=((1<<a1)|(1<<a2)|(1<<a3)|(1<<a4)|(1<<a5))>>1;
              carcost[idx] = min(carcost[idx], d[0][a1]+d[a1][a2]+d[a2][a3]+d[a3][a4]+d[a4][a5]+d[a5][n+1]+5*(1+(a2!=a1)+(a3!=a2)+(a4!=a3)+(a5!=a4)));
            }
    cost[0]=0;
    for(i=0; i<(n+4)/5; i++){
      for(j=0; j<(1<<n); j++)
        if(carcost[j] < 1000000000000LL)
          for(k=(1<<n)-1; (k&=~j)>=0; k--)
            cost2[k|j] = min(cost2[k|j], max(cost[k], carcost[j]));
      memcpy(cost, cost2, sizeof(cost));
    }
    printf("%lld\n", cost[(1<<n)-1]);
  }
  return 0;
}
