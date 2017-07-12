#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
int cmp (const void *pa, const void *pb)
{
  int*a=(int*)pa;
  int*b=(int*)pb;
  return *a < *b ? -1 : 1;
}

int main()
{
  ll a[4];
  for (int i=0; i<4; i++)
  	scanf("%lld", &a[i]);
  qsort(a, 4, sizeof(ll), cmp);
  ll ans=a[3]+2*a[0];
  a[1]-=a[0];
  ans+=3*(a[1]/3);
  if (a[1]%3==2)
  {
  	ans++;
  }
  printf("%lld\n", ans);
}























































