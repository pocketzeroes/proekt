#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int read(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
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
///////////////////////////////////////////
enum{MAXR = 55};
enum{MAXN = MAXR * MAXR * 4};
int R, K, vis[MAXN * 2], marked[MAXN * 2], A[MAXR * 2][MAXR * 2], ans;
vec adj[MAXN * 2];

void addEdge(int v, int w){
    pb(adj[v], w);
    pb(adj[w], v);
}
void dfs(int v){
    if (marked[v]){
        ans++;
        return;
    }
    if (vis[v])
        return;
    vis[v] = true;
    for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
        dfs(w);
    }
}
int main(){
    for(int i=(0);i<(MAXR * 2);i++)
        for(int j=(0);j<(MAXR * 2);j++)
            A[i][j] = -1;
    R=read();
    K=read();
    int x;
    for(int i=(0);i<(K);i++){
        x = read();
        marked[x] = true;
    }
    R++;
    int ind1 = 1, ind2 = MAXN, cur = R;
    for(int i=(0);i<(2 * R - 1);i++){
        if (i == 0 || i == 2 * R - 2)
            for(int j=(0);j<(cur);j++)
                A[i][j] = ind2++;
        else {
            A[i][0] = ind2++;
            for(int j=(1);j<(cur - 1);j++)
                A[i][j] = ind1++;
            A[i][cur - 1] = ind2++;
        }
        if (i < R - 1)
            cur++;
        else
            cur--;
    }
    for(int i=(0);i<(2 * R - 1);i++)
        for (int j = 0; A[i][j + 1] != -1; j++)
            addEdge(A[i][j], A[i][j + 1]);
    for(int i=(0);i<(R - 1);i++)
        for (int j = 0; A[i][j] != -1; j++){
            addEdge(A[i][j], A[i + 1][j]);
            addEdge(A[i][j], A[i + 1][j + 1]);
        }
    for(int i=(R);i<(2 * R - 1);i++)
        for (int j = 0; A[i][j] != -1; j++){
            addEdge(A[i][j], A[i - 1][j]);
            addEdge(A[i][j], A[i - 1][j + 1]);
        }
    dfs(MAXN);
    printf("%d\n", ans);
    return 0;
}
