#include <stdio.h>
#include <string.h>

int cost[101];
int best[101];
int last[101];
char adj[101][101];

int z,i,j,k,m,n,e,progress;
int main(){
  while ((1 == scanf("%d",&n)) && n != -1){
    memset(adj ,0,sizeof(adj ));
    memset(last,0,sizeof(last));
    for (i=1;i<=n;i++)
      best[i] = 0x3fffffff;
    for (i=1;i<=n;i++){
       scanf("%d%d",&e,&m);
       cost[i] = -e;
       for (j=0;j<m;j++){
          scanf("%d",&k);
          adj[i][k] = 1;
       }
    }
    best[1] = -100;
    for (z=0;;z++){
      progress = 0;
      for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) {
          if (adj[i][j] && best[i] < 0 && best[i] + cost[j] < 0 && best[i] + cost[j] < best[j]){
            best[j] = best[i] + cost[j];
            progress = 1;
            last[j] = z;
          }
        }
      if (!progress || best[n] < 0)
        break;
      if (z == n) {
        for (i=1;i<=n;i++)
          if (last[i] != z)
            best[i] = 0x3fffffff;
        for (i=1;i<=n;i++)
          cost[i] = 0;
      }
    }
    if (best[n] < 0)
      printf("winnable\n");
    else 
      printf("hopeless\n");
  }
  if (n != -1)
    printf("missing end delimiter\n");
  return 0;
}
