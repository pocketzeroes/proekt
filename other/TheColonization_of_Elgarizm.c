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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ MAXN =(int)1e6+6};
vec graph[MAXN];
int color[MAXN];

void dfs(int u, int c){
    if(color[u] & c)
        return;
    color[u] |= c;
    for(int z=0;z<graph[u].sz;z++){int v = graph[u].ptr[z];
        dfs(v, c ^ 3);
    }
}
int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int occ[n]; fill(occ, n, -1);
    for(int i = 0; i < m; ++i){
        int x;
        while(scanf("%d", &x)==1){
            --x;
            if (x < 0) 
                break;
            if (occ[x] == -1)
                occ[x] = i;
            else{
                pb(graph[occ[x]], i);
                pb(graph[i], occ[x]);
            }
        }
    }
    for(int i = 0; i < m; ++i)
        if(color[i] == 0)
            dfs(i, 1);
    bool valid = true;
    for(int i = 0; i < m; ++i)
        valid &= color[i] < 3;
    puts(valid ? "YES" : "NO");
    return 0;
}
