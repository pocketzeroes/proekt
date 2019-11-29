#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

enum{ N   =(int)5e4+1,
      INF =(int)1e9+1};
int K, n, m, O;
typedef struct{
    int a[5][5];
}mat;
mat I, adj[N], t[4*N];

mat merge(mat a, mat b){
    mat res; dfill(res.a, K, K, INF);
    for(int x=0; x<K; x++)
        for(int y=0; y<K; y++)
            for(int z=0; z<K; z++)
                res.a[x][y] = fmin(a.a[x][z] + b.a[z][y], res.a[x][y]);
    return res;
}
void build(){
    for(int i=0; i<n; i++)
        t[n+i] = adj[i];
    for(int i=n-1; i>=1; i--)
        t[i] = merge(t[i<<1], t[i<<1|1]);
}
mat query(int l, int r){
    mat resl = I;
    mat resr = I;
    for(l+=n, r+=n+1; l<r; l>>=1, r>>=1){
        if(l&1) resl = merge(resl, t[l++]);
        if(r&1) resr = merge(t[--r], resr);
    }
    return merge(resl, resr);
}
int main(){
    scanf("%d %d %d %d", &K, &n, &m, &O);
    dfill(I.a, K, K, INF);
    for(int i=0; i<n; i++)
        adj[i] = I;
    for(int i=0; i<K; i++)
        I.a[i][i]=0;
    for(int i=0,u,v,w; i<m; i++){
        scanf("%d %d %d", &u, &v, &w);
        adj[u/K].a[u%K][v%K] = w;
    }
    build();
    for(int i=0,a,b; i<O; i++){
        scanf("%d %d", &a, &b);
        mat res=query(a/K, b/K-1);
        if(a/K==b/K || res.a[a%K][b%K] == INF)
            puts("-1");
        else
            printf("%d\n", res.a[a%K][b%K]);
    }
    return 0;
}
