#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ N = 1005};
enum{ E = 5005};
int n, m, q, e;
int head[N], nxt[E], to[E];
int low[N], idx[N], dfs;
int br[E];
int pr[N];

int fs(int x){
    if(pr[x] == x )return x;
    else{        pr[x] = fs(pr[x]);
          return pr[x];}
}
void us(int a, int b)
{
    a = fs(a), b = fs(b);
    if(a != b){
        pr[a] = b;
    }
}
void init()
{
    e = 0;
    memset(head, -1, sizeof head);
    for(int i = 0 ; i < n ; i++)
        pr[i] = i;
}
void addEdge(int f, int t)
{
    nxt[e] = head[f];
    head[f] = e;
    to[e++] = t;
}
void addBiEdge(int a, int b)
{
    addEdge(a, b);
    addEdge(b, a);
}
void DFS(int u, int p)
{
    low[u] = idx[u] = ++dfs;
    for(int k = head[u] ; ~k ; k = nxt[k]){
        int v = to[k];
        if (idx[v] == 0){
            DFS(v, u);
            low[u]=min(low[u],low[v]);
            if(low[v]>idx[u])
                br[k] = br[1^k] = 1;
        }
        else if(p!=v)
            low[u]=min(low[u],idx[v]);
    }
}
int main(){
    scanf("%d %d %d", &n, &m, &q);
    init();
    for(int i = 0 ; i < m ; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        addBiEdge(--a, --b);
    }
    memset(idx, 0, sizeof idx);
    for(int i = 0 ; i < n ; i++)
        if(!idx[i])
            DFS(i, -1);
    for(int i = 0 ; i < n ; i++){
        for(int k = head[i]; ~k ; k = nxt[k]){
            int j = to[k];
            if(br[k]){
                us(i, j);
            }
        }
    }
    while(q--){
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        printf("%d\n", (fs(a) == fs(b)) );
    }
    return 0;
}
