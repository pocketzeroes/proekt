#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int main(){
    long long ans;
    int n, i, mn, A[100009];
    for(i=0,scanf("%d",&n); i<n; ++i)
        scanf("%d", A+i);
    for(ans=i=0, qsort(A, n, sizeof(int), cmp), mn=A[n/2]; i<n; ++i) 
        ans += abs(A[i]-mn);
    printf("%lld\n",ans),exit(0);
}
