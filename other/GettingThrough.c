#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}
int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}

enum{ N = 1000};
int X[N], Y[N], R[N];
double Len[N+2][N+2];
double All[((N+2)*(N+1))/2];
int BFSqueue[N+2];
bool OnQueue[N+2];


double eucldis (int i, int j){
  return sqrt((long long)(X[i]-X[j])*(X[i]-X[j]) + (long long)(Y[i]-Y[j])*(Y[i]-Y[j]));
}
int main(){
  int cases, casenr, w, n, m, i, j, wall1, wall2, lb, ub, mid, cur, last;
  double maxlen;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){
    scanf("%d\n%d\n", &w, &n);
    for (i = 0; i < n; i++)
      scanf("%d %d %d\n", &X[i], &Y[i], &R[i]);
    wall1 = n;
    wall2 = n+1;
    All[0] = Len[wall1][wall2] = Len[wall2][wall1] = w / 2.0;
    m = 1;
    for (i = 0; i < n; i++){
      All[m++] = Len[i][wall1] = Len[wall1][i] = max(0.0, (X[i] - R[i]) / 2.0);
      All[m++] = Len[i][wall2] = Len[wall2][i] = max(0.0, (w - X[i] - R[i]) / 2.0);
      for (j = i+1; j < n; j++)
        All[m++] = Len[i][j] = Len[j][i] = max(0.0, (eucldis(i, j) - R[i] - R[j]) / 2.0);
    }
    qsort(All, m, sizeof(double), cmpDbl);
    lb = -1;
    ub = m-1;
    while (lb < ub-1){
      mid = (lb + ub) / 2;
      maxlen = All[mid];
      memset(OnQueue, false, sizeof(OnQueue));
      BFSqueue[0] = wall1;
      OnQueue[wall1] = true;
      last = 1;
      for (cur = 0; cur < last && !OnQueue[wall2]; cur++){
        i = BFSqueue[cur];
        for (j = 0; j < n+2; j++)
          if (!OnQueue[j] && Len[i][j] <= maxlen){
            BFSqueue[last++] = j;
            OnQueue[j] = true;
          }
      }
      if (OnQueue[wall2])
        ub = mid;
      else
        lb = mid;
    }
    printf("%lf\n", All[ub]);
  }
  return 0;
}
