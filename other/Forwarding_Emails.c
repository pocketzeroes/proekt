#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

/*///////////////////*/
vec adj[50002], compo[50002];
vec order, vua[50002];
bool visited[50002];
int  cost   [50002];
int mxNode , mxCost;

int dfs1(int u,int x)
{
    compo[x].ptr = pushback(compo[x].ptr, &compo[x].sz ,u);
    visited[u] = true;
    int i ,sz = vua[u].sz;
    for( i = 0 ; i < sz ; i++)
    {
        int v = vua[u].ptr[i];
        if(!visited[ v ]) 
            dfs1( v,x );
    }
}
int dfs2(int u)
{
    visited[u]=true;
    int i , v, sz = adj[u].sz;
    for( i = 0 ; i < sz ; i++ ){
        v = adj[u].ptr[i];
        if( visited[ v ] ) 
            break;
        dfs2(v);
    }
    return v;
}
void dfs3(int u)
{
    order.ptr = pushback(order.ptr, &order.sz ,u);
    visited[u] = true;
    int i ,sz = adj[u].sz;
    for( i = 0 ; i < sz ; i++ ){
        int v = adj[u].ptr[i];
        if(visited[v])
            return;
        dfs3(v);
    }
}
int dfs4( int u )
{
    if (!cost [u]) 
        return cost [u] = dfs4 (adj [u].ptr[0]) + 1;
    return cost [u];
}
void cycle(vec*my)
{
    order.sz=0;
    memset(visited,false,sizeof visited);
    int i, cycleNode = dfs2(my->ptr[0]);
    memset(visited,false,sizeof visited);
    dfs3(cycleNode);
    for( i = 0 ; i < order.sz ; i++ ){
        cost[ order.ptr[i] ]  = order.sz;
    }
    int sz = my->sz;
    for( i = 0 ; i < sz ; i++){
        int u = my->ptr[i];
        if( cost[u] == 0 ) 
            dfs4(u);
    }
    for( i = 0 ; i < sz ; i++ ){
        if( cost[ my->ptr[i] ] > mxCost ){
            mxCost = cost[ my->ptr[i] ];
            mxNode = my->ptr[i];
        }
        else if(cost[ my->ptr[i] ] == mxCost ){
            mxNode = min( mxNode , my->ptr[i] );
        }
    }
}
void clear(int n)
{
    int i;
    mxNode  = 1, mxCost = -9999999;
    for( i = 0 ; i <= n ;i++ ){
        vua[i].sz=0;
        adj[i].sz=0;
        cost[i]= 0;
        visited[i]=false;
        compo[i].sz=0;
    }
}
int main()
{
    int t,i,j,cs=1;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        clear(n);
        for(i=1; i<=n; i++)
        {
            int u,v;
            scanf("%d %d", &u, &v);
            adj[u].ptr = pushback(adj[u].ptr, &adj[u].sz ,v);
            vua[u].ptr = pushback(vua[u].ptr, &vua[u].sz ,v);
            vua[v].ptr = pushback(vua[v].ptr, &vua[v].sz ,u);
        }
        int totalCompo = 0;
        for( i = 1 ; i <= n ; i++)
        {
            if(visited[i])
                continue;
            dfs1(i,totalCompo);
            totalCompo++;
        }
        for( i = 0 ; i < totalCompo ; i++ ){
            cycle(&compo[i]);
        }
        printf("Case %d: %d\n", cs++, mxNode);
    }
    return 0;
}



















































