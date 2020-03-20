#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
void iota(int*arr, int sz, int beg){
  for(int i=0; i<sz; i++)
    arr[i] = i;
}
enum{ MAXN = 505   };
enum{ MAXV = 505050};

//typedef struct{
    int pa[MAXV];
    void init(){
        iota(pa, MAXV, 0);
    }
    int dfind(int x){
        return pa[x]=(pa[x] == x?x:dfind(pa[x]));
    }
    bool uni(int p, int q){
        p = dfind(p);
        q = dfind(q);
        if(p == q)
            return 0;
        pa[q] = p;
        return 1;
    }
//}disjo;


int n, m;
char str [MAXN][MAXN];
int  C   [MAXN][MAXN][4];
vecp gph [MAXV];
vecp comp[MAXV];
int  vis [MAXV],
     ban [MAXV][2];
int  ans [MAXV];

void dfs(int x, int c){
    if(vis[x]){
        if(vis[x] != c)
            ans[0] = ans[1] =(int)1e9;
        return;
    }
    vis[x] = c;
    ans[(c-1)]++;
    if(ban[x][c-1])
        ans[0] = 1e9;
    if(ban[x][(c-1)^1])
        ans[1] =(int)1e9;
    for(int z=0;z<gph[x].sz;z++){pair uv = gph[x].ptr[z];
        int u = uv.first;
        int v = uv.second;
        if(u)
            dfs(v, 3-c);
        else
            dfs(v, c);
    }
}
int find(pair*arr, int asz, pair a){
    for(int i=0; i<asz; i++)
        if(cmpP(arr[i], a)==0)
            return i;
    return-1;
}
void erase(vecp*v, int pos){
    for(int i=pos; i<v->sz-1; i++)
        v->ptr[i] = v->ptr[i+1];
    (v->sz)--;
}
int main(){
    scanf("%d %d", &n, &m);
    int vtx = 0;
    init();
    for(int i=0; i<n; i++)
        scanf("%s", str[i]);
    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++){
            if(i < n)
                C[i][j][0] = ++vtx;
            if(j < m)
                C[i][j][1] = ++vtx;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(str[i][j] == '#')
                continue;
            if(str[i][j] == '.'){
                uni(C[i][j][0], C[i][j+1][0]);
                uni(C[i][j][1], C[i+1][j][1]);
            }
            if(str[i][j] == '/'){
                uni(C[i][j][0]  , C[i][j][1]);
                uni(C[i][j+1][0], C[i+1][j][1]);
            }
            if(str[i][j] == '\\'){
                uni(C[i][j][0]  , C[i+1][j][1]);
                uni(C[i][j+1][0], C[i][j][1]);
            }
        }
    }
    int idx = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(str[i][j] == 'V'||
               str[i][j] == 'H'){
                int L = dfind(C[i][j][0]);
                int R = dfind(C[i][j+1][0]);
                int U = dfind(C[i][j][1]);
                int D = dfind(C[i+1][j][1]);
                pbp(comp[L], newpair(idx, (str[i][j] == 'H')) );
                pbp(comp[R], newpair(idx, (str[i][j] == 'H')) );
                pbp(comp[U], newpair(idx, (str[i][j] == 'V')) );
                pbp(comp[D], newpair(idx, (str[i][j] == 'V')) );
                idx++;
            }
            if(str[i][j] == '#'){
                int L = dfind(C[i][j][0]);
                int R = dfind(C[i][j+1][0]);
                int U = dfind(C[i][j][1]);
                int D = dfind(C[i+1][j][1]);
                pbp(comp[L], newpair(-1, -1) );
                pbp(comp[R], newpair(-1, -1) );
                pbp(comp[U], newpair(-1, -1) );
                pbp(comp[D], newpair(-1, -1) );
            }
        }
    }
    for(int i=0; i<=vtx; i++){
        if(comp[i].sz <= 1)
            continue;
        int fnd = find(comp[i].ptr, comp[i].sz, newpair(-1, -1));
        if(fnd==-1){
            int x = comp[i].ptr[0].first;
            int y = comp[i].ptr[1].first;
            int z = comp[i].ptr[0].second != comp[i].ptr[1].second;
            pbp(gph[x], newpair(z, y) );
            pbp(gph[y], newpair(z, x) );
        }
        else{
            erase(&comp[i], fnd);
            if(cmpP(comp[i].ptr[0], newpair(-1, -1))==0)
                continue;
            ban[comp[i].ptr[0].first][comp[i].ptr[0].second] = 1;
        }
    }
    int ret=0;
    for(int i=0; i<vtx; i++){
        if(!vis[i]){
            ans[0] = ans[1] = 0;
            dfs(i, 1);
            ret += fmin(ans[0], ans[1]);
            if(ret>(int)1e7)
                break;
        }
    }
    if(ret>(int)1e7)
       ret = -1;
    printf("%d\n", ret);
    return 0;
}
