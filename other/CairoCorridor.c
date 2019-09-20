#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////////////////////////////////////
#define clr( a , x ) memset ( a , x , sizeof a )
enum{ MAXN = 300005 };
enum{ mod  = 13 };
enum{ INF  = 0x3f3f3f3f};

typedef struct{
    int x, y, v;
}Node;
Node newNode(int x, int y, int v){
    return(Node){x,y,v};
}
vec  G[MAXN],
     now;
int  dfn[MAXN],
     low[MAXN],
     dfs_clock;
int  cut[MAXN];
int  vis[MAXN];
int  S[MAXN],
     top;
int  a[255][255],
     b[255][255];
int  idx[255][255][2],
     cnt;
Node is[MAXN];
int  num[4];
int  p[MAXN];
int  n , m;

void tarjan(int u , int pre){
    int v;
    low[u] = dfn[u] = ++ dfs_clock;
    S[top ++] = u;
    int son = 0 , pre_cnt = 0;
    for ( int i = 0; i < G[u].sz; ++ i ){
        v = G[u].ptr[i];
        if ( v == pre && pre_cnt == 0 ){
            pre_cnt ++;
            continue;
        }
        if ( !dfn[v] ){
            ++ son;
            tarjan ( v , u );
            if ( low[u] > low[v] )
                low[u] = low[v];
            if ( u != pre && low[v] >= dfn[u] )
                cut[u] = 1;
        }
        else
            low[u] = fmin(low[u] , dfn[v]);
    }
    if ( u == pre && son > 1 )
        cut[u] = 1;
    -- top;
}
int F(int x){
    return p[x] == x ? x : ( p[x] = F ( p[x]));
}
void add(int x , int y){
    if ( is[x].v ){
        if ( b[is[x].x][is[x].y] )
            return;
    }
    else{
        if ( a[is[x].x][is[x].y] )
            return;
    }
    if ( is[y].v ){
        if ( b[is[y].x][is[y].y] )
            return;
    }
    else{
        if ( a[is[y].x][is[y].y] )
            return;
    }
    p[F ( x )] = F ( y );
    pb(G[x], y);
}
void dfs(int u , int f){
    vis[u] = 1;
    pb(now, u);
    for(int i = 0; i < G[u].sz; ++ i ){
        int v = G[u].ptr[i];
        if ( v == f )
            continue;
        if ( vis[v] )
            continue;
        dfs(v , u);
    }
}
int addval(int x , int y , int v , int f){
    if ( ( x + y ) % 2 == 0 ){
        if ( v == 0 && y == 1 )
            num[0] += f;
        if ( v == 1 && y == m )
            num[1] += f;
        if ( x == 1 )
            num[2] += f;
        if ( x == n )
            num[3] += f;
    }
    else{
        if ( y == 1 )
            num[0] += f;
        if ( y == m )
            num[1] += f;
        if ( v == 0 && x == 1 )
            num[2] += f;
        if ( v == 1 && x == n )
            num[3] += f;
    }
}
int can_del(int o){
    int x = is[o].x,
        y = is[o].y ,
        v = is[o].v ,
        ok = 1;
    addval ( x , y , v , -1 );
    if ( !num[0] || !num[1] || !num[2] || !num[3] )
        ok = 0;
    addval ( x , y , v , 1 );
    return ok;
}
void solve (){
    cnt = 0;
    scanf ( "%d%d" , &n , &m );
    for ( int i = 1; i <= n; ++ i ){
        for ( int j = 1; j <= m; ++ j ){
            scanf ( "%1d%1d" , &a[i][j] , &b[i][j] );
            idx[i][j][0] = ++ cnt;
            is[cnt] = newNode ( i , j , 0 );
            idx[i][j][1] = ++ cnt;
            is[cnt] = newNode ( i , j , 1 );
        }
    }
    for ( int i = 1; i <= cnt; ++i)
        G[i].sz=0;
    for ( int i = 1; i <= cnt; ++i)
        p[i] = i;
    for ( int i =  1; i <= n; ++ i ){
        for ( int j = 1; j <= m; ++ j ){
            add ( idx[i][j][0] , idx[i][j][1] );
            add ( idx[i][j][1] , idx[i][j][0] );
            if ( ( i + j ) % 2 == 0 ){
                if ( i < n ) add ( idx[i][j][0] , idx[i + 1][j][0] );
                if ( i > 1 ) add ( idx[i][j][0] , idx[i - 1][j][1] );
                if ( j > 1 ) add ( idx[i][j][0] , idx[i][j - 1][0] );
                if ( j > 1 ) add ( idx[i][j][0] , idx[i][j - 1][1] );
                if ( i < n ) add ( idx[i][j][1] , idx[i + 1][j][0] );
                if ( i > 1 ) add ( idx[i][j][1] , idx[i - 1][j][1] );
                if ( j < m ) add ( idx[i][j][1] , idx[i][j + 1][0] );
                if ( j < m ) add ( idx[i][j][1] , idx[i][j + 1][1] );
            }
            else{
                if ( j < m ) add ( idx[i][j][0] , idx[i][j + 1][0] );
                if ( j > 1 ) add ( idx[i][j][0] , idx[i][j - 1][1] );
                if ( i > 1 ) add ( idx[i][j][0] , idx[i - 1][j][0] );
                if ( i > 1 ) add ( idx[i][j][0] , idx[i - 1][j][1] );
                if ( j < m ) add ( idx[i][j][1] , idx[i][j + 1][0] );
                if ( j > 1 ) add ( idx[i][j][1] , idx[i][j - 1][1] );
                if ( i < n ) add ( idx[i][j][1] , idx[i + 1][j][0] );
                if ( i < n ) add ( idx[i][j][1] , idx[i + 1][j][1] );
            }
        }
    }
    clr ( dfn , 0 );
    clr ( low , 0 );
    clr ( cut , 0 );
    top = dfs_clock = 0;
    for ( int i = 1; i <= cnt; ++ i )
        if ( !dfn[i] )
            tarjan ( i , i );
    int ans = -1;
    clr ( vis , 0 );
    for ( int i = 1; i <= cnt; ++ i ){
        if ( F ( i ) == i ){
            if ( is[i].v ){
                if ( b[is[i].x][is[i].y] )
                    continue;
            }
            else{
                if ( a[is[i].x][is[i].y] )
                    continue;
            }
            now.sz=0;
            clr ( num , 0 );
            dfs ( i , i );
            for ( int j = 0; j < now.sz; ++ j ){
                int x = is[now.ptr[j]].x,
                    y = is[now.ptr[j]].y,
                    v = is[now.ptr[j]].v;
                addval ( x , y , v , 1 );
            }
            if ( !num[0] || !num[1] || !num[2] || !num[3] )
                continue;
            int ok = 1;
            for ( int j = 0; j < now.sz; ++ j){
                if ( !cut[now.ptr[j]] ){
                    if ( can_del(now.ptr[j]))
                        ok = 0;
                }
            }
            if ( ok )
                ans = fmax(ans, now.sz);
        }
    }
    if ( ans == -1 )
        printf ( "NO MINIMAL CORRIDOR\n" );
    else
        printf ( "%d\n" , ans );
}
int main (){
    int T = 0;
    scanf ( "%d" , &T );
    for(int i = 1; i <= T; ++i)
        solve();
    if ( T )
        return 0;
    return 0;
}
