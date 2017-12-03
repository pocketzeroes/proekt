#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


double p[16][15000];
double s[15000];

void swap(double*nums, int i, int j){
   double t    = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int cmp(const void *pa, const void*pb){
    double*a=(double*)pa;
    double*b=(double*)pb;
    return(*b < *a)?-1:1;
}
void rec(int l,int r,int v){
  if (l+1==r) {p[v][l]=1; return;}
  int m=(l+r)/2;
  rec(l, m, v+1);
  rec(m, r, v+1);
  for (int i=l; i<m; i++)
    for (int j=m; j<r; j++)
      if (p[v+1][i] || p[v+1][j])
        p[v][i]+=p[v+1][i]*p[v+1][j]*s[i]/(s[i]+s[j]),
        p[v][j]+=p[v+1][i]*p[v+1][j]*s[j]/(s[i]+s[j]);
}
int main(){
  int n;
  scanf("%d", &n);
  int n2=1;
  while (n2<n)
      n2*=2;
  for(int i=n; i--;)
      scanf("%lf", &s[i]);
  qsort(s, n-1, sizeof(double), cmp);
  for (int i=0; i<n2-n; i++)
      swap(s, n2-1-i*2, n-1-i);  
  n=n2;
  rec(0, n, 0);
  printf("%lf\n", p[0][n-1]);
}
