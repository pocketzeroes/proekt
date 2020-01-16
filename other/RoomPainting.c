#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    ll res = 0LL;
    int x;
    while(m-- > 0){
        scanf("%d", &x);
        int it = lower_bound(a, n, x);
        res += a[it]-x;
    }
    printf("%lld\n", res);
    return 0;
}
