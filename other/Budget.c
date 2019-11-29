#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXV = 5000};
int f[MAXV][MAXV];
int c[MAXV][MAXV];
int infty = 1<<30;

inline int rc(int i,int j){
  return c[i][j] - f[i][j];
}
void init(int m, int n){
  for (int i = 0; i < m+n+2; ++i)
    for (int j = 0; j < m+n+2; ++j){
      f[i][j] = 0;
      c[i][j] =  (i > 0 && i <= m && j > m && j <= n+m) ? infty : 0;
    }
}
int bfs(int s, int t, int nv, int p[]){
  int qh = 0, qt = 0;
  char v[MAXV];
  int q[MAXV];
  memset(v,0,nv);
  q[qt++] = s;
  p[s] = -1;
  v[s] = 1;
  while (qh < qt) {
    int u = q[qh++];
    if (u == t)
      return 1;
    for (int w = 0; w < nv; ++w)
      if (!v[w] && rc(u,w)>0) {
        v[w] = 1;
        q[qt++] = w;
        p[w] = u;
      }
  }
  return 0;
}
int augment(int t, int p[]){
  int slack = infty;
  for(int u = t; p[u] != -1; u = p[u])
    slack = fmin(slack, rc(p[u],u));
  for(int u = t; p[u] != -1; u = p[u])
    f[u][p[u]] = -(f[p[u]][u] += slack);
  return slack;
}
int maxf(int s, int t, int nv){
  int p[MAXV];
  int fl = 0;
  for (int i = 1; i < nv; ++i)
    fl += f[s][i];
  while(bfs(s,t,nv,p))
    fl += augment(t,p);
  return fl;
}
int impossible(char*s){
  printf("IMPOSSIBLE\n");
  return 0;
}
int solve(int caseno){
  int n,m,nc;
  int x,y,a;
  int ilo, ihi, jlo, jhi;
  char cmp;
  int s,t;
  int rsum = 0;
  int csum = 0;
  if (caseno != 1)
    printf("\n");
  scanf("%d %d", &m, &n);
  init(m,n);
  s = 0;
  t = m+n+1;
  for (int i = 1; i <= m; ++i)  {
    scanf("%d", &c[s][i]);
    rsum += c[s][i];
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[m+i][t]);
    csum += c[m+i][t];
  }
  scanf("%d", &nc);
  while(nc--) {
    if (scanf("%d %d %c %d", &x, &y, &cmp, &a) != 4)
      fprintf(stderr,"READ ERROR!!!\n");
    ilo = x ? x : 1;
    ihi = x ? x : m;
    jlo = y ? y : 1;
    jhi = y ? y : n;
    for (int i = ilo; i <= ihi; ++i)
      for (int j = jlo; j <= jhi; ++j)
        switch (cmp) {
          case '=':
            c[i][m+j] = fmin(c[i][m+j],a);
            c[m+j][i] = fmin(c[m+j][i],-a);
            break;
          case '>':
            c[m+j][i] = fmin(c[m+j][i],-(1+a));
            break;
          case '<':
            c[i][m+j] = fmin(c[i][m+j],a-1);
            break;
          default: fprintf(stderr,"OP ERROR!!!\n");
        }
  }
  if (csum != rsum)
    return impossible("csum != rsum");
  for (int i = 1; i <= m; ++i)
    for (int j = m+1; j <= n+m; ++j)
      if ((x=rc(j,i)) < 0) {
        f[i][j] = -(f[j][i] += x);
        f[s][i] = -(f[i][s] += x);
        f[j][t] = -(f[t][j] += x);
      }
  for (int i = 0; i <= m+n+1; ++i)
    for (int j = 0; j <= n+m+1; ++j)
      if (rc(i,j) < 0)
        return impossible("No legal initial flow");
  if (maxf(s,t,m+n+2) != rsum)
    return impossible("max flow != rowsum");
  for (int i = 1; i <= m; ++i)
    for (int j = m+1; j <= n+m; ++j)
      printf("%d%s", f[i][j], j<m+n ? " " : "\n");
  return 1;
}
int main(){
  int ncases;
  scanf("%d", &ncases);
  for (int i=1; i <=ncases; ++i)
    solve(i);
  return 0;
}
