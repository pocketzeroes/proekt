#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
double tl[100001], tr[100001];
double xl[100001], xr[100001];
double vl[100001], vr[100001];
int last;
int ln, rn;

typedef struct{
  int x, v;
}vehicle;
vehicle a[100001];

int cmp1(const void*pa, const void*pb){
  vehicle*a=(vehicle*)pa;
  vehicle*b=(vehicle*)pb;
  return(a->v > b->v || a->v == b->v && a->x > b->x)?-1:1;
}
int cmp2(const void*pa, const void*pb){
  vehicle*a=(vehicle*)pa;
  vehicle*b=(vehicle*)pb;
  return(a->v < b->v || a->v == b->v && a->x < b->x)?-1:1;
}
int main(){
  scanf("%d", &n);
  int mini, maxi;
  while(n){
    mini = maxi = 0;
    for (int i = 0; i < n ; ++i )
      scanf("%d%d", &a[i].x, &a[i].v);
    qsort(a, n, sizeof(vehicle), cmp1);
    tl[0] = 0;
    xl[0] = a[0].x;
    vl[0] = a[0].v;
    last = 0;
    for (int i = 1; i < n ; ++i ){
      while (last >= 0 && (a[i].v == vl[last] || a[i].v * tl[last] + a[i].x <= xl[last]))
        --last;
      if (last < 0){
        last = 0;
        tl[last] = 0;
        xl[last] = a[i].x;
        vl[last] = a[i].v;
      }
      else {
        double tx = a[i].x + tl[last] * a[i].v;
        tl[last+1] = (tx - xl[last]) / (vl[last] - a[i].v) + tl[last];
        xl[last+1] = tl[last+1] * a[i].v + a[i].x;
        vl[last+1] = a[i].v;
        ++last;
      }
    }
    ln = last + 1;
    tl[ln]=300000;
    qsort(a, n, sizeof(vehicle), cmp2);
    tr[0] = 0;
    xr[0] = a[0].x;
    vr[0] = a[0].v;
    last = 0;
    for (int i = 1; i < n ; ++i ){
      while (last >= 0 && (a[i].v == vr[last] || a[i].v * tr[last] + a[i].x >= xr[last]))
        --last;
      if (last < 0){
        last = 0;
        tr[last] = 0;
        xr[last] = a[i].x;
        vr[last] = a[i].v;
      }
      else {
        double tx = a[i].x + tr[last] * a[i].v;
        tr[last+1] = (tx - xr[last]) / (vr[last] - a[i].v) + tr[last];
        xr[last+1] = tr[last+1] * a[i].v + a[i].x;
        vr[last+1] = a[i].v;
        ++last;
      }
    }
    rn = last + 1;
    tr[rn] = 300000;
    double ans = 300000;
    int j = 0;
    for (int i = 0; i < ln; ++i){
      while (tr[j] <= tl[i])
        ++j;
      --j;
      if (j < 0)
        j = 0;
      if ((tl[i]-tr[j])*vr[j]+xr[j] - xl[i] < ans)
        ans = (tl[i]-tr[j])*vr[j]+xr[j] - xl[i];
    }
    j = 0;
    for (int i = 0; i < rn; ++i){
      while (tl[j] <= tr[i])
        ++j;
      --j;
      if (j < 0)
        j = 0;
      if (xr[i] - (xl[j]+(tr[i]-tl[j])*vl[j]) < ans)
        ans = xr[i] - (xl[j]+(tr[i]-tl[j])*vl[j]);
    }
    if (ans < 0)
      ans = 0;
    printf("%.2lf\n", ans);
    break;
    scanf("%d", &n);
  }
  return 0;
}
