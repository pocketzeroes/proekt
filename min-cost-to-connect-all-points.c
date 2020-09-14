#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef struct{
    int s, t, d;
}node;
node e[1000005];
int f[1005];

int cmpN(const void*pa, const void*pb){
    node*x=(node*)pa;
    node*y=(node*)pb;
    return(x->d < y->d)?-1:1;
}
int A(int x){
    return x<0?-x:x;
}
int get(int x){
    if(f[x]==x)
        return x;
    return f[x]=get(f[x]);
}
int minCostConnectPoints(int**points, int pointsSz, int*points0sz){
    clr(f);
    clr(e);
    int n=pointsSz,i,j,m=0,ans=0;
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            e[++m].d=A(points[i][0]-points[j][0])+A(points[i][1]-points[j][1]);
            e[m].s=i;
            e[m].t=j;
        }
    }
    qsort(e+1, m, sizeof(node), cmpN);
    for(i=0; i<n; i++)
        f[i]=i;
    for(i=1; i<=m; i++){
        if(get(e[i].s) != get(e[i].t)){
            ans += e[i].d;
            f[get(e[i].s)] = get(e[i].t);
        }
    }
    return ans;
}
