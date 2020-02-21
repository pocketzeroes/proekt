#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
enum{nmax = 1005};
int n, k, a[nmax], mid, req;
int main(){
    scanf("%d %d", &n, &k);
    for(int i=1;i<=n;++i)
        scanf("%d", &a[i]);
    qsort(a+1, n, sizeof(int), cmp);
    mid = a[n/2+1];
    int act = n/2+1;
    while(act <= n && a[act] == mid)
        ++req, ++act;
    if(req > k)
        printf("%d\n", mid);
    else
        printf("%d\n", mid+1);
    return 0;
}
