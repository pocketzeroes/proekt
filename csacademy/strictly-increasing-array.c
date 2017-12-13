#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

int w;
int *a;

void A(int x){
  int l=1, r=w, m;
  while(l<=r){
    m=(l+r)>>1;
    if(a[m]<=x)
      l=m+1;
    else
      r=m-1;
  }
  a[++r]=x;
  if(r>w)
    w=r;
}
int main(){
  int n, i, x;
  int *p, *q;
  scanf("%d", &n);
  a=(int*)malloc((n+10)*sizeof(int));
  for(q=(p=a)+n; p<q; p++)
    *p=INT_MAX;
  w=0;
  for(i=1; i<=n; i++)
  {
    scanf("%d", &x);
    if((x-=i)>=0)
      A(x);
  }
  printf("%d\n", n-w);
  free(a);
  return 0;
}
