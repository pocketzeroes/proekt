#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pair minP(pair a,pair b){return cmpP(a,b)<0?a:b;}

int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
/////////////////////
enum{mxN=(int)2e5};

int n, m, a[mxN], b[mxN], c[mxN], va[mxN], p[mxN], bm[1<<19];
pair lm[1<<19];

pair mxp={INT_MAX, INT_MAX};

pair qry(int x, int i, int l2, int r2){
  if(l2==r2)
    return bm[i]>=x?lm[i]:mxp;
  int m2=(l2+r2)/2;
  return x>bm[2*i+1]?qry(x, 2*i, l2, m2):minP(lm[i], qry(x, 2*i+1, m2+1, r2));
}
void upd(int l1, pair x, int y, int i, int l2, int r2){
  if(l2==r2){
    lm[i]=x;
    bm[i]=y;
    return;
  }
  int m2=(l2+r2)/2;
  if(l1<=m2)
    upd(l1, x, y, 2*i, l2, m2);
  else
    upd(l1, x, y, 2*i+1, m2+1, r2);
  bm[i] = fmax(bm[2*i], bm[2*i+1]);
  lm[i] = qry(bm[2*i+1], 2*i, l2, m2);
}
int main(){
  scanf("%d %d", &n, &m);
  for(int i=0; i<n+m; ++i)
    scanf("%d %d %d", &a[i], &b[i], &c[i]);
  memcpy(va, a, 4*(n+m));
  qsort(va, n+m, sizeof(int), cmp);
  for(int i=0; i<n+m; ++i)
    p[i] = lower_bound(va, n+m, a[i]);
  for(int i=0; i<n; ++i)
    upd(p[i], (pair){c[i], i}, b[i], 1, 0, n+m-1);
  for(int i=0; i<m; ++i){
    pair qq = qry(1, 1, 0, n+m-1);
    int j = qq.second;
    printf("%d\n", j+1);
    upd(p[j], (pair){0,0}, 0, 1, 0, n+m-1);
    upd(p[n+i], (pair){c[n+i], n+i}, b[n+i], 1, 0, n+m-1);
  }
  return 0;
}
