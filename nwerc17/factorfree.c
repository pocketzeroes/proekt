#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int*a;
int*parent;
int*prv;
int*nxt;

void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}

void prepare(int n, int LIM){
    int div[LIM+1];
    memset(div, 0, sizeof(div));
    for (int i = 2; i <= LIM; ++i)
        if (!div[i])
            for (int j = i; j <= LIM; j += i)
                div[j] = i;
    int last[LIM+1]; fill(last, LIM+1, -1);
    prv = calloc(n, sizeof(int)); fill(prv, n, -1);
    nxt = calloc(n, sizeof(int)); fill(nxt, n, n );
    for (int i = 0; i < n; ++i){
        int v = a[i];
        while(v != 1){
#define l last[div[v]]
            if (l < i){
                prv[i] = max(prv[i], l);
                if(l != -1)
                    nxt[l] = min(nxt[l], i);
            }
            l = i;
            v /= div[v];
        }
    }
}
bool solve(int L, int R, int par){
    if (R-L <= 0) 
        return true;
    for (int i = L, j = R-1; i <= j; ++i, --j) {
        parent[i] = par;
        if (prv[i] < L && nxt[i] >= R)
            return solve(L, i, i) && solve(i+1, R, i);
        parent[j] = par;
        if (prv[j] < L && nxt[j] >= R)
            return solve(L, j, j) && solve(j+1, R, j);
    }
    return false;
}
int main(void){
    int n, max_a = 0;
    scanf("%d", &n);
    a = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        max_a = max(a[i], max_a);
    }
    prepare(n, max_a);
    parent = calloc(n, sizeof(int));
    if(solve(0, n, -1))
        for (int i = 0; i < n; ++i)
            printf("%d ", parent[i]+1);
    else
        printf("impossible\n");    
}
