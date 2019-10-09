#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void iota(int*arr, int sz, int beg){
  for(int i=0; i<sz; i++)
    arr[i] = i;
}

int main(){
    int n;
    scanf("%d", &n);
    int outdeg[n]; clr(outdeg);
    int idx   [n]; clr(idx   );
    for(int i=1; i<n; ++i){
        char w[n];
        scanf("%s", w);
        for(int j=0; j<i; ++j)
            ++outdeg[w[j]=='1' ? i : j];
    }
    iota(idx, n, 0);
int cmp(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(outdeg[*a] < outdeg[*b])?-1:1;
}
    qsort(idx, n, sizeof(int), cmp);
    int ans = 0, 
        cur = 0;
    for(int pos=0; pos<n; ++pos){
        int i = idx[pos];
        cur += outdeg[i] - pos;
        ans = fmax(ans, cur);
    }
    printf("%d\n", ans);
    return 0;
}
