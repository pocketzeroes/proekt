#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

typedef struct Edge{
    int  to;
    struct Edge*nxt;
}Edge;
Edge*newEdge(int t, Edge*n){
    Edge*rv=calloc(1, sizeof(Edge));
    rv->to  = t;
    rv->nxt = n;
    return rv;
}

int main(){
    
    int N = in_nextInt();
    int deg[N+1]; clr(deg);
    Edge*g[N+1]; clr(g);
    for(int i=0; i<N; i++){
        int a = in_nextInt();
        int b = in_nextInt();
        deg[a]++;
        deg[b]++;
        g[a] = newEdge(b, g[a]);
        g[b] = newEdge(a, g[b]);
    }
    bool vis[N+1]; clr(vis);
    int  qu [N];   clr(qu);
    int back = 0;
    for(int i = 1; i<=N; i++)
        if(deg[i]==1)
            qu[back++] = i;
    while(back>0){
        int v = qu[--back];
        vis[v] = true;
        for(Edge*e = g[v];; e=e->nxt){
            if(!vis[e->to]){
                printf("%d %d\n", v, e->to);
                if(--deg[e->to]==1)
                    qu[back++] = e->to;
                break;
            }
        }
    }
    for(int i=1; i<=N; i++){
        if(!vis[i]){
            int start=i;
            for(int j=i, nxt=-1; nxt!=start; j=nxt){
                vis[j] = true;
                for(Edge*e=g[j]; e!=NULL; e=e->nxt)
                    if(!vis[e->to])
                        nxt = e->to;
                if(nxt==j)
                    nxt = start;
                printf("%d %d\n", j, nxt);
            }
        }
    }
    return 0;
}
