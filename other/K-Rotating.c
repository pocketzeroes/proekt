#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=(int)1e5+7, M=400};
int f[M][N], g[M][N], a[20][N], num[N];
bool vis[N];

int main(){
   int n, m, Q;
   scanf("%d%d%d", &n, &m, &Q);
   int BS = fmax(10, (int)sqrt(m));
   for(int i=0;i<m;i+=BS){
      for(int j=1;j<=n; j++)
         f[i/BS][j]=j, g[i/BS][j]=j;
   }
   int op;
   for(int i=1; i<= Q ; i++){
      scanf("%d", &op);
      if(op==1){
         int d, x;
         scanf("%d%d", &d, &x); x--;
         int B = x/BS;
         for(int j=x; j>=B*BS;j--){
            if(!vis[j])
               continue;
            int len=num[j];
            for(int k=0;k<len;k++){
               if(a[k][j]==d){d=a[(k+1)%len][j];break;}
            }
         }
         for(int j=B-1; j>=0; j--) d=f[j][d];
         printf("%d\n", d);
      }
      else{
         int len, x;
         scanf("%d%d", &len, &x);
         x--;
         num[x]=len;
         vis[x]=true;
         for(int j=0;j<len;j++)
            scanf("%d", &a[j][x]);
         int B=x/BS;
         for(int j=B*BS; j<fmin(B*BS+BS, n); j++){
            if(!vis[j])continue;
            int len=num[j];
            for(int k=0;k<len;k++)
               f[B][a[k][j]]=a[k][j], g[B][a[k][j]]=a[k][j];
         }
         for(int j = fmin(B*BS+BS,n)-1; j>=B*BS; j--){
            if(!vis[j])
               continue;
            int len=num[j];
            for(int k=0;k<len;k++){
               f[B][g[B][a[k][j]]]=a[(k+1)%len][j];
            }
            int tmp=g[B][a[len-1][j]];
            for(int k=len-1;k>0;k--){
               g[B][a[k][j]]=g[B][a[k-1][j]];
            }
            g[B][a[0][j]]=tmp;
         }
      }
   }
   return 0;
}