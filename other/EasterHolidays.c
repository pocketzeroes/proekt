#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int m, n, k;
int **lifts, **slopes;
int *tl, *ts;
int *dl, *ds;
int *pl, *ps;
int *pl_best, *ps_best;
int *best;

void read_input(){
  int i, j, a, b;
  scanf("%d%d%d", &n, &m, &k);
  lifts = (int **) malloc((n + 1) * sizeof(int *));
  slopes = (int **) malloc((n + 1) * sizeof(int *));
  for (i = 1; i <= n; i++){
    lifts[i] = (int *) malloc((n + 1) * sizeof(int));
    slopes[i] = (int *) malloc((n + 1) * sizeof(int));
    for (j = 1; j <= n; j++)
      lifts[i][j] = slopes[i][j] = -1;
  }
  for (i = 0; i < m; i++){
    scanf("%d%d", &a, &b);
    scanf("%d", &slopes[a][b]);
  }
  for (i = 0; i < k; i++){
    scanf("%d%d", &a, &b);
    scanf("%d", &lifts[b][a]);
  }
}
void free_graphs(){
//  int i;
//  for (i = 1; i <= n; i++){
//    free(lifts[i]);
//    free(slopes[i]);
//  }
//  free(lifts);
//  free(slopes);
}
void top_sort(int **a, int *t){
  int *c, *candidate;
  int i, j, ncand;
  c = (int *) malloc((n + 1) * sizeof(int));
  candidate = (int *) malloc(n * sizeof(int));
  for (i = 1; i <= n; i++)
    c[i] = 0;
  ncand = 0;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (a[i][j] > 0) c[j]++;
  for (i = 1; i <= n; i++)
    if (!c[i])
      candidate[ncand++] = i;
  for (i = 1; i <= n; i++){
    t[i] = candidate[--ncand];
    for (j = 1; j <= n; j++){
      if (a[t[i]][j] > 0)
        if (!--c[j])
          candidate[ncand++] = j;
    }
  }
//  free(c);
//  free(candidate);
}
int maxi(int a, int b, int p, int *isnew){
  *isnew = 0;
  if ((a == -1) && (b == -1))
    return -1;
  if (a == -1){
    *isnew = 1;
    return b + p;
  }
  if (b == -1)
    return a;
  if (a > b + p)
    return a;
  *isnew = 1;
  return b + p;
}
int mini(int a, int b, int p, int *isnew){
  *isnew = 0;
  if ((a == -1) && (b == -1))
    return -1;
  if (a == -1){
    *isnew = 1;
    return b + p;
  }
  if (b == -1)
    return a;
  if (a > b + p){
    return b + p;
    *isnew = 1;
  }
  return a;
}
void ext_path(int **a, int *t, int *d, int *pred, int u, int maximize){
  int i, j, p, isnew;
  for (i = 1; i <= n; i++)
    if ((d[i] = a[u][i]) > 0)
      pred[i] = u;
  d[u] = 0; p = 0;
  for (i = 1; i <= n; i++)
    if (t[i] == u)
      p = i;
  for (i = p + 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (a[t[i]][j] > 0){
        if (maximize)
          d[j] = maxi(d[j], d[t[i]], a[t[i]][j], &isnew);
        else
          d[j] = mini(d[j], d[t[i]], a[t[i]][j], &isnew);
        if(isnew)
          pred[j] = t[i];
      }
}
int restore_path(int a, int b){
  int a1, i, j, k, aux;
  a1 = a;
  i = 1;
  best[1] = a;
  while (a1 != b)
    a1 = best[++i] = pl_best[a1];
  j = ++i;
  best[i] = a;
  while (a != b)
    a = best[++i] = ps_best[a];
  i--;
  k = i;
  while (j < k){
    aux = best[j];
    best[j] = best[k];
    best[k] = aux;
    j++; k--;
  }
  return i;
}
int main(){
  float ratio, max_ratio;
  int a, b, i, j, len;
  int ncases;
  scanf("%d", &ncases);
  while (ncases--){
    read_input();
    tl = (int *) malloc((n + 1) * sizeof(int));
    dl = (int *) malloc((n + 1) * sizeof(int));
    pl = (int *) malloc((n + 1) * sizeof(int));
    pl_best = (int *) malloc((n + 1) * sizeof(int));
    ts = (int *) malloc((n + 1) * sizeof(int));
    ds = (int *) malloc((n + 1) * sizeof(int));
    ps = (int *) malloc((n + 1) * sizeof(int));
    ps_best = (int *) malloc((n + 1) * sizeof(int));
    best = (int *) malloc((n + 1) * sizeof(int));
    top_sort(lifts, tl);
    top_sort(slopes, ts);
    max_ratio = 0;
    for (i = 1; i <= n; i++){
      ext_path(lifts, tl, dl, pl, i, 0);
      ext_path(slopes, ts, ds, ps, i, 1);
      for (j = 1; j <= n; j++)
        if ((j != i) && (dl[j] != -1) && (ds[j] != -1)){
          ratio = (float)ds[j] / (float)dl[j];
          if (ratio > max_ratio){
            max_ratio = ratio;
            a = i; b = j;
            memcpy(pl_best, pl, (n + 1) * sizeof(int));
            memcpy(ps_best, ps, (n + 1) * sizeof(int));
          }
        }
    }
    len = restore_path(b, a);
    for (i = 1; i <= len; i++)
      printf("%d ", best[i]);
    printf("\n%.3f\n", max_ratio);
//    free(tl); free(dl); free(pl); free(pl_best);
//    free(ts); free(ds); free(ps); free(ps_best);
//    free(best);
//    free_graphs();
  }
  return 0;
}
