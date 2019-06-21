#include <stdio.h>

enum{ MAX_JUNCTIONS =  200};
enum{ MAX_STREETS   = 1000};

int jstreets[MAX_JUNCTIONS][MAX_JUNCTIONS];
int jnbr    [MAX_JUNCTIONS];
int streets [MAX_STREETS][2];
int cap     [MAX_JUNCTIONS];
int par     [MAX_JUNCTIONS];
int path    [MAX_JUNCTIONS];
int vis     [MAX_JUNCTIONS];
int nstr;

int augment(int who, int cnt){
  if (cap[who]<0)
    return cnt;
  else{
    if (!vis[who]){
      int i,ans;
      ans = 0;
      vis[who] = 1;
      for (i=0;i<jnbr[who] && !ans; i++){
        int sel = jstreets[who][i];
        if (streets[sel][0] == who){
          path[cnt] = sel;
          ans = augment(streets[sel][1],cnt+1);
        }
      }
      return ans;
    }
    else
      return 0; 
  }  
}
int main(){
  int i, j, k, T, n, m, augpath;
  scanf("%d",&T);
  for (i=0;i<T;i++){
    scanf("%d %d",&n,&m);
    for (j=0;j<n;j++){
      par [j]=0;
      cap [j]=0;
      jnbr[j]=0;
    }
    nstr=0; 
    for (j=0;j<m;j++){
      int x,y,one;
      scanf("%d %d %d", &x, &y, &one);  
      x--, y--;
      if (!one && x!=y){
        streets[nstr][0]=x;
        streets[nstr][1]=y;
        jstreets[x][jnbr[x]++] = nstr;
        jstreets[y][jnbr[y]++] = nstr;
        nstr++;
      }
      cap[x]++;
      cap[y]--;
      par[x]++;
      par[y]++;
    }
    augpath=1;
    for (j=0;j<n && augpath; j++)
      if (par[j] & 1)
        augpath=0;
    for (j=0;j<n && augpath; j++){
      while (cap[j]>0 && augpath){
        int q,plen;
        for (q=0;q<n;q++)
          vis[q]=0;
        if (plen=augment(j,0)){
          for (k=0;k<plen;k++){
            int tmp;
            tmp = streets[path[k]][0];
            streets[path[k]][0]=streets[path[k]][1];
            streets[path[k]][1]=tmp;
          }
          cap[j]-=2;
          cap[streets[path[plen-1]][0]]+=2;
        }
        else
          augpath=0;
      }
    }
    if (augpath)
      printf("possible\n");
    else
      printf("impossible\n");     
  }
  return 0;
}
