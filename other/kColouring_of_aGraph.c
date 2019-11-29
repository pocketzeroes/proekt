#pragma GCC optimize "-O3"
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

enum{ maxn=50000+10};
enum{ maxc=5       };
typedef long long ll;
ll f[maxn][maxc];
int n,m,k,p,rt;
int vis[maxn],
    col[maxn];
vec g  [maxn],
    son[maxn],
    spe;
ll ret;

void dfs(int u, int fa){
    vis[u]=1;
    for(int z=0;z<g[u].sz;z++){int v=g[u].ptr[z];
        if(v!=fa){
            if(vis[v]){
                if(vis[v]==1&&vis[u]==1){
                    vis[u]=2; 
                    pb(spe, u);
                }
            }
            else{
                pb(son[u], v);
                dfs(v,u);
            }
        }
    }
}
void DFS(int u, int c){
    if(k<c)
        return;
    memset(f[u], 0, sizeof(f[u]));
    if(vis[u]==2)
        f[u][col[u]]=1;
    else
        for(int i=0;i<=c;i++)
            f[u][i]=1;
    for(int z=0;z<g[u].sz;z++){int v=g[u].ptr[z];
        if(vis[v]==2)
            f[u][col[v]]=0;
    }
    for(int z=0;z<son[u].sz;z++){int v=son[u].ptr[z];
        DFS(v, c);
        for(int i=0;i<=c;i++){
            f[u][i] *= (f[v][c+1]-f[v][i]+p);
            f[u][i] %= p;
        }
    }
#define sum f[u][c+1]
    for(int i=0;i<=c;i++){
        sum += (f[u][i]*(i==c?(ll)(k-c):1))%p;
        sum %= p;
    }
    if(u==rt){
        for(int i=k;i>k-c;i--){
            sum*=i;
            sum%=p;
        }
        ret=(ret+sum)%p;
    }
}
void gen(int dep, int c){
    if(dep==spe.sz)
        DFS(rt,c);
    else for(int i=0;i<=c;i++){
        col[spe.ptr[dep]]=i;
        gen(dep+1, fmax(c, i+1));
    }
}
int main(){
    scanf("%d %d %d %d", &n, &m, &k, &p);
    for(int i=0; i<m; i++){
        int u,v;
        scanf("%d%d", &u, &v);
        pb(g[u], v);
        pb(g[v], u);
    }
    ll ans=1;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            ret=0;
            spe.sz=0;
            dfs(rt=i, 0);
            gen(0,0);
            ans = ans*ret%p;
        }
    }
    printf("%d\n", (int)ans);
    return 0;
}
