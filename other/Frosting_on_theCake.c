#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

enum{ MAXN = 100000};
long sumbs[4];
int n;
int a[MAXN+1];
int b[MAXN+1];
long results[3]; 

int main(){
    int i, j, m;
    scanf("%d",&n);
    memset(sumbs, 0, 4*sizeof(long));
    for (i = 1; i<=n; ++i) 
        scanf("%d",&a[i]); 
    for (i = 1; i<=n; ++i){
        scanf("%d",&b[i]);
        m = i%3; 
        if (!m)
            m = 3;
        sumbs[m] += b[i];
    }
    memset(results, 0, 3*sizeof(long));
    for (i = 1; i <= n; ++i) {
        m = i%3;
        if (!m)
            m = 3;
        for (j = 1; j<=3; ++j)
            results[(m+j)%3]+=a[i]*sumbs[j];
    }
    printf("%ld %ld %ld\n", results[0], results[1], results[2]);
    return 0;
}
