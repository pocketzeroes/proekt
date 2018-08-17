#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define mod 1000000007
int n, i, ii, nr, p, u, ok, u2;
int v[205], w[105], c[205], d[205][2];

int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

int main(){
    scanf("%d", &n);
    for(i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for(ii = 1; ii <= n; ii++){
        p = u = 1;
        c[1] = w[ii];
        while(p <= u){
            ok = 0;
            for(i = 1; i <= nr; i++){
                if(v[i] == c[p]){
                    ok = 1;
                    swap(v, i, nr);
                    nr--;
                    break;
                }
            }
            if(ok == 0){
                v[++nr] = c[p];
                qsort(v+1, nr, sizeof(int), cmp);
                u2 = 1;
                for(i = 2; i <= nr; i++){
                    if(v[i] == v[u2] + 1)
                        v[u2] += 2;
                    else{
                        if(v[i] == v[u2])
                            c[++u] = v[i];
                        else
                            v[++u2] = v[i];
                    }
                }
                nr = u2;
            }
            else{
                qsort(v+1, nr, sizeof(int), cmp);
                if(c[p] == 1)
                    c[++u] = 2;
                else{
                    if(c[p] == 2){
                        c[++u] = 1;
                        c[++u] = 3;
                    }
                    else{
                        c[++u] = c[p] - 2;
                        c[++u] = c[p] + 1;
                    }
                }
            }
            p++;
        }
        d[0][0] = 1;
        d[0][1] = 0;
        for(i = 1; i <= nr; i++){
            d[i][0] = (d[i - 1][0] + d[i - 1][1]) % mod;
            d[i][1] = ( ( (v[i] - v[i - 1]) / 2 ) * 1LL * d[i - 1][1] + ( (v[i] - v[i - 1] - 1) / 2 ) * 1LL * d[i - 1][0]) % mod;
        }
        printf("%d\n", (d[nr][0] + d[nr][1]) % mod );
    }
    return 0;
}
