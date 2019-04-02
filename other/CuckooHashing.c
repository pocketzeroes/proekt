#include <stdio.h>

enum{ MAXN = 10000};
int t;
int n,m;
int table[MAXN];
int E[MAXN][2];

int main(){
  int i;
  scanf("%d",&t);
  while(t--){
    int infinite=0;
    scanf("%d %d",&m,&n);
    for (i=0;i<m;i++)
      scanf("%d %d",&E[i][0],&E[i][1]);
    for (i=0;i<n;i++)
      table[i]=-1;
    for (i=0;i<m && !infinite;i++){
      if (table[E[i][0]]==-1)
        table[E[i][0]]=i;
      else if (table[E[i][1]]==-1)
        table[E[i][1]]=i;
      else{
        int cur=E[i][0];
        int who=i;
        while (table[cur]>-1 && !infinite){
          int evict=table[cur];
          int where=E[evict][0]+E[evict][1]-cur;
          table[cur]=who;
          who=evict;
          cur=where;
          infinite=(who==i) && (cur==E[i][0]);
        }
        table[cur]=who;
      }
    }
    if (infinite)
      printf("rehash necessary\n");
    else
      printf("successful hashing\n");
  }
  return 0;
}
