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

int main(){
    int l[2], n;
    scanf("%d %d %d", &l[0], &l[1], &n);
    int a[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    int other[n+1][2];
    for(int k=0; k<2; ++k){
        for(int i=0; i<n; ++i){
           #define u other[i][k]
            if(i == 0)
                u = n - 1;
            else
                u = other[i - 1][k];
            while(u >= 0 && a[u] + a[i] > l[k])
                u--;
#undef u
        }
    }
    int res = -1;
    for(int i=0; i<n; ++i)
      if(other[i][0] > i)
        for(int j=0; j<(n); ++j)
          if(other[j][1] > j && i != j)
            for(int k = other[i][0]; k >= other[i][0]-3 && k > i; k--)
              if(k != j)
                for(int v=other[j][1]-3; v<(other[j][1]+1); ++v)
                  if(v > j && k != v && i != v)
                    res = fmax(res, a[i] + a[k] + a[j] + a[v]);
    if(res == -1)
        printf("Impossible\n");
    else
        printf("%d\n", res);
    return 0;
}
