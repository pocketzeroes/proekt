#include <stdio.h>

enum{ MAXNM = 1000};

int n, m;
int adj[MAXNM][MAXNM];

int freecol(int x){
  int i;
  int col[MAXNM];
  for (i=0;i<n*m;i++) col[i]=0;
  for (i=0;i<n*m;i++)
    if (adj[x][i]<0)
      col[-adj[x][i]]=1;
  for (i=1;i<n*m && col[i];i++);
  return -i;
}
int locatecol(int x,int c){
  int i;
  for (i=0;i<n*m && adj[x][i]!=c;i++);
  return i;
}
void recol(int x, int y){
  int vis[MAXNM];
  int who[MAXNM];
  int wcol[MAXNM];
  int i;
  int fy=freecol(y);
  int nc=locatecol(x,fy);
  int cur = 1;
  for (i=0;i<n*m;i++) vis[i]=0;
  vis[y] = 1;
  who[0] = y;
  wcol[0] = fy;
  while (nc!=n*m && !vis[nc]) {
    vis[nc] = 1;
    y=nc;
    fy = freecol(y);
    who[cur] = y;
    wcol[cur++] = fy;
    nc = locatecol(x, fy);
  }
  if (nc==n*m) {
    for (i=0;i<cur;i++) {
      adj[x][who[i]] = wcol[i];
      adj[who[i]][x] = wcol[i];
    }
  }
  else {
    int fx = freecol(x);
    int nn=locatecol(nc,fx);
    adj[x][nc] = fx;
    adj[nc][x] = fx;
    while (nn!=n*m) {
      int nnn= locatecol(nn,fy);
      adj[nc][nn] = fy;
      adj[nn][nc] = fy;
      nc=nn;
      nn=nnn;
      int tmp=fx;
      fx=fy;
      fy=tmp;
    }
    recol(x,who[0]);
  }
}
int main(){
  int i,j,k,l;
  scanf("%d %d",&n,&m);
  for (i=0;i<n;i++) 
    for (j=0;j<m;j++) 
      for (k=0;k<n;k++) 
        for (l=0;l<m;l++) 
          adj[j*n+i][l*n+k] = (j!=l);
  for (i=0;i<n*m;i++)
    for (j=0;j<n*m;j++)
      if (adj[i][j]>0) {
        recol(i,j);
      }
  int matches=n*(m-1)*n*m/2;
  for (k=1;k<n*(m-1)+2 && matches;k++) {
    for (i=0;i<n*m;i++) {
      for (j=i+1;j<n*m;j++) {
        if (adj[i][j]==-k) {
          matches--;
          printf("%c%d-%c%d ",65+(i/n),(i%n)+1,65+(j/n),(j%n)+1);
        }
      }
    }
    printf("\n");
  }
  return 0;
}
