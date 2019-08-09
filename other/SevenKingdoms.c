#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
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

enum{ maxn = 2000};
int n;
vec adj   [maxn*2];
vec adjrev[maxn*2];
int val   [maxn];
int marker,dfst,dfstime[maxn*2],dfsorder[maxn*2];
int group[maxn*2];

inline int other(int v){return v<n?v+n:v-n;}
inline int var(int v){return v<n?v:v-n;}
inline int type(int v){return v<n?1:0;}

void satclear(){
    for(int i=0;i<maxn+maxn;i++) {
        adj   [i].sz = 0;
        adjrev[i].sz = 0;
    }
}
void dfs(int v){
    if(dfstime[v]!=-1)
        return;
    dfstime[v]=-2;
    int deg = adjrev[v].sz;
    for(int i=0;i<deg;i++)
        dfs(adjrev[v].ptr[i]);
    dfstime[v] = dfst++;
}
void dfsn(int v){
    if(group[v]!=-1)
        return;
    group[v]=marker;
    int deg=adj[v].sz;
    for(int i=0;i<deg;i++)
        dfsn(adj[v].ptr[i]);
}
void addedge(int a, int b){
    int oa = other(a);
    int ob = other(b);
    adj[oa].ptr   = pushback(adj[oa].ptr, &adj[oa].sz, b);
    adjrev[a].ptr = pushback(adjrev[a].ptr, &adjrev[a].sz, ob);
    adj[ob].ptr   = pushback(adj[ob].ptr, &adj[ob].sz, a);
    adjrev[b].ptr = pushback(adjrev[b].ptr, &adjrev[b].sz, oa);
}
int solve(){
    dfst=0;
    memset(dfstime,-1,sizeof dfstime);
    for(int i=0;i<n+n;i++)
        dfs(i);
    memset(val,-1,sizeof val);
    for(int i=0;i<n+n;i++)
        dfsorder[n+n-dfstime[i]-1]=i;
    memset(group,-1,sizeof group);
    for(int i=0;i<n+n;i++) {
        marker=i;
        dfsn(dfsorder[i]);
    }
    for(int i=0;i<n;i++) {
        if(group[i]==group[i+n])
            return 0;
        val[i]=(group[i]>group[i+n])?0:1;
    }
    return 1;
}
int main(){
    int m;
    while (scanf("%d %d", &n, &m) != EOF){
        bool adjmatrix[n][n]; memset(adjmatrix, 0, sizeof(adjmatrix));
        for(int i=0; i<m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adjmatrix[u - 1][v - 1] = adjmatrix[v - 1][u - 1] = true;
        }
        int color[n]; fill(color, n, 2);
        for (int i = 0; i < 2; i++){
            color[i] = i;
            for (int j = 0; j < n; j++)
                if (adjmatrix[i][j])
                    color[j] = 3 + i;
        }
        bool possible = true;
        for (int i = 2; i < n && possible; i++)
            for (int j = i + 1; j < n && possible; j++)
                if (!adjmatrix[i][j])
                    if (color[i] == 2 && color[j] == 2)
                        possible = false;
                    else if (color[i] == 2)
                        addedge(other(j), other(j));
                    else if (color[j] == 2)
                        addedge(other(i), other(i));
                    else if (color[i] != color[j])
                        addedge(other(i), other(j));
                    else{
                        addedge(i, j);
                        addedge(other(i), other(j));
                    }
        if (possible && solve()){
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < n; j++)
                    if (adjmatrix[i][j])
                        if (val[j])
                            color[j] = 2;
                        else
                            color[j] = i;
        }
        else
            possible = false;
        if (possible)
            for (int i = 0; i < 2; i++){
                bool first = true;
                for (int j = 0; j < n; j++)
                    if (color[j] == i){
                        if (!first)
                            printf(" ");
                        printf("%d", j + 1);
                        first = false;
                    }
                    printf("\n");
            }
        else
            printf("impossible\n");
    }
    return 0;
}
