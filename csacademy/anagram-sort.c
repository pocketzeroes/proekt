#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 505};
int n;
int a[N], b[N], c[N];
int x[N], res[N];

int ask(){
    for(int i=0; i<n; ++i){
        printf("%d ", c[i]);
        fflush(stdout);
    }
    puts("");
    int ret=0;
    scanf("%d", &ret);
    return ret;
}
int main(){
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%d", &b[i]);
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            c[j] = b[(i + j) % n];
        x[i] = ask();
        if(x[i] == 0)
            return 0;
    }
    for(int i=0; i<n; ++i){
        int v0, v1;
        v0 = v1 = 0;
        for(int j=i+1; j<n; ++j)
            v0 += b[j] == b[i];
        for(int j=0; j<n; ++j)
            v1 += b[j] == b[i];
        res[(x[i] - x[(i + 1) % n] + n - v1) / 2 + v0] = b[i];
    }
    for(int i=0; i<n; ++i){
        printf("%d ", res[i]);
        fflush(stdout);
    }
    int rep;
    scanf("%d", &rep);
    return 0;
}
