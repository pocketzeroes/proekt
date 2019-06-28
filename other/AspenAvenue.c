#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

int N, L, W, dropy[3000];
double best[1100][1100], step;

double Best(int l, int r){
  if (l < 0 || r < 0)
    return 1e30;
  if(l+r == 0)
    return 0;
#define res best[l][r]
  if (res == 0) {
    res = 1e30;
    int ty = dropy[l+r-1];
    res = min(res, hypot(0, step*(l-1)-ty) + Best(l-1, r));
    res = min(res, hypot(W, step*(r-1)-ty) + Best(l, r-1));
    ++res;
  }
  return res-1;
}
int main(){
  scanf("%d %d %d", &N, &L, &W);
  int t[2], p[2];
  step = 1.0*L / (N/2-1);
  for (int i = 0; i < N; ++i)
    scanf("%d", dropy+i);
  qsort(dropy, N, sizeof(int), cmp);
  memset(best, 0, sizeof(best));
  printf("%.10lf\n", Best(N/2, N/2));
  return 0;
}
