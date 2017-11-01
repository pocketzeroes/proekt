#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////
int col  [50000];
int n, m;
vec g    [50000];
int dist[20][50000], cnt[50000], subCnt[50000], par[50000], dep[50000];
int sum  [50000], subSum[50000];
vec sub  [50000];
int gsz   [50000];
bool used[50000];
int tot  [50000];
int calcDep;

void calcSizes(int v, int p){
    gsz[v] = 1;
    for(int i=0;i<g[v].sz;i++){int to = g[v].ptr[i];
        if (used[to] && to != p) {
            calcSizes(to, v);
            gsz[v] += gsz[to];
        }
    }
}
void cdCalc(int v, int p){
    if (p == -1)
        dist[calcDep][v] = 0;
    else
        dist[calcDep][v] = dist[calcDep][p] + 1;
    for(int i=0; i<g[v].sz; i++){int to = g[v].ptr[i];
        if (used[to] && to != p)
            cdCalc(to, v);
    }
}
void cdBuild(int v, int p){
    calcSizes(v, -1);
    int tot = gsz[v];
    bool ok = false;
    int pp = -1;
    while (!ok){
        ok = true;
        for(int i=0; i<g[v].sz; i++){int to = g[v].ptr[i];
            if (used[to] && to != pp && gsz[to] * 2 > tot){
                pp = v;
                v = to;
                ok = false;
                break;
            }
        }
    }
    used[v] = false;
    if (p == -1)
        dep[v] = 0;
    else{
        dep[v] = dep[p] + 1;
        sub[p].ptr = pushback(sub[p].ptr, &sub[p].sz, v);
    }
    par[v] = p;
    calcDep = dep[v];
    cdCalc(v, -1);
    for(int i=0; i<g[v].sz; i++){int to = g[v].ptr[i];
        if (used[to])
            cdBuild(to, v);
    }
}
void addNode(int v){
    ++cnt[v];
    for (int i = dep[v] - 1, p = par[v], pp = v; i >= 0; --i) {
        ++cnt[p];
        sum[p] += dist[i][v];
        ++subCnt[pp];
        subSum[pp] += dist[i][v];
        pp = p;
        p = par[p];
    }
}
void removeNode(int v){
    for (int i = dep[v] - 1, p = par[v], pp = v; i >= 0; --i) {
        --cnt[p];
        sum[p] -= dist[i][v];
        --subCnt[pp];
        subSum[pp] -= dist[i][v];
        pp = p;
        p = par[p];
    }
    --cnt[v];
}
int nodeGet(int v){
    int ans = sum[v];
    for (int i = dep[v] - 1, p = par[v], pp = v; i >= 0; --i) {
        ans += sum[p] - subSum[pp] + (int)(cnt[p] - subCnt[pp]) * dist[i][v];
        pp = p;
        p = par[p];
    }
    return ans;
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i)
        scanf("%d", col + i);
    for(int i = 0; i < n - 1; ++i){
        int from, to;
        scanf("%d %d", &from, &to), --from, --to;
        g[from].ptr = pushback(g[from].ptr, &g[from].sz, to  );
        g[to  ].ptr = pushback(g[to  ].ptr, &g[to  ].sz, from);
    }
    for(int i = 0; i < n; ++i) 
        used[i] = true;
    cdBuild(0, -1);
    for(int i = 0; i < n; ++i) 
        addNode(i);
    for(int i = 0; i < n; ++i) 
        tot[i] = nodeGet(i);
    for(int i = 0; i < n; ++i) 
        if(col[i] == 0)
            removeNode(i);
    for(int i = 0; i < m; ++i){
        int qt, v;
        scanf("%d %d", &qt, &v), --v;
        if (qt == 1) {
            if (col[v] == 0)
                addNode(v);
            else
                removeNode(v);
            col[v] ^= 1;
        } 
        else{
            int ans = nodeGet(v);
            if (col[v] == 0)
                ans = tot[v] - ans;
            printf("%d\n", ans);
        }
    }
    return 0;
}




















