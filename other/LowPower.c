#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int n, k;
int*arr;

bool possible(int diff){
    if(arr[1] - arr[0] > diff)
        return false;
    int cnt = 0;
    for(int i = 0; i <2*n*k-1; ++i){
        if(i > cnt*k*2)
            return false;
        if(arr[i+1] - arr[i] <= diff){
            cnt++;
            if(cnt == n)
                return true;
            i++;
        }
    }
    return false;
}
int main() {
    scanf("%d %d", &n, &k);
    arr = calloc(2*n*k, sizeof(int));
    for(int z=0;z<2*n*k;z++)
        scanf("%d", &arr[z]);
    qsort(arr, 2*n*k, sizeof(int), cmp);
    int start = -1, end = (int)1e9, mid;
    while(end-start > 1){
        mid = (start+end)>>1;
        if(possible(mid))
            end = mid;
        else
            start = mid;
    }
    printf("%d\n", end);
    return 0;
}
