#include<stdio.h>
#include<string.h>

enum{ SIZE = 100};

char g[SIZE][SIZE];

int i,j,k,m,n,p,x,a,size;

int v[SIZE], cnt[SIZE][SIZE], is, best[SIZE][SIZE], prev[SIZE][SIZE];

void dump(int p, int x){
   if (p)
      dump(p-1,prev[p][x]);
   printf(" %d", x+1);
}
int main(){
   while (1 == scanf("%d",&n) && n != -1) {
      memset(g,0,sizeof(g));
      memset(cnt,0,sizeof(cnt));
      for (i=0;i<n;i++) {
         scanf("%d%d",&j,&k);
         g[k-1][j-1] = 1;
      }
      scanf("%d",&m);
      m--;
      for (i=0;i<=m;i++) {
         scanf("%d",&v[i]);
         v[i]--;
      }
      scanf("%d",&p);
      p--;
      for (a=0;a<m;a++) {
         for (i=0;i<SIZE;i++){
            is = 0;
            for (size=1;i+size<SIZE;size++) {
               for(j=v[a];j<v[a+1];j++) {
                  is |= g[i+size-1][j];
                  if (is) {
                     cnt[i][i+size]++;
                     break;
                  }
               }
            }
         }
      }
      for (i=0;i<SIZE;i++)
         for (j=0;j<SIZE;j++)
            best[i][j] = -1;
      best[0][0] = 0;
      for (n=0;n<p;n++) {
         for (j=SIZE-1;j>0;j--){
            for (i=0;i<j;i++){
               if (cnt[i][j] + best[n][i] > best[n+1][j]){
                  best[n+1][j] = cnt[i][j] + best[n][i];
                  prev[n+1][j] = i;
               }
            }
         }
      }
      printf("%d",p+1);
      dump(p,SIZE-1);
      printf("\n");
   }
   if (n != -1)
      printf("missing end delimiter\n");
   return 0;
}
