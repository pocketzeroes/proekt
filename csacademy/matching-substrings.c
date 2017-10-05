#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") 
#pragma GCC option("arch=native","tune=native","no-zero-upper") 
#pragma GCC target("avx") 
#include <x86intrin.h> 

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
inline vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ N = 1200000};
vec edges [N];
int go[26][N];
int id    [N];
char* st  [N];
int s     [N];
int path  [N];
int deg   [N];
int fr = 0;
int ac = 0;
int cn = 0;



int newNode(){
    int u = fr++;
    for (int j = 0; j < 26; j++)
        go[j][u] = -1;
    id[u] = -1;
    return u;
}
int add(int*s, int n){
    int v = 0;
    char w[100000]; int wSz=0;
    for (int j = 0; j < n; j++) {
        if (go[s[j]][v] < 0)
            go[s[j]][v] = newNode();
        v = go[s[j]][v];
        w[wSz++] = (char) ('a' + s[j]);
    }
    if (id[v] < 0){
        w[wSz] = '\0';
        st[cn] = strdup(w);
        id[v] = cn++;
    }
    return id[v];
}
void dfs(int v){
    while(edges[v].sz>0){
        int to = edges[v].ptr[edges[v].sz-1];
        edges[v].sz--;
        dfs(to);
    }
    path[ac++] = v;
}
int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    
    if(k == 1){
        for (int i = 0; i < n; i++){
            int c = getchar();
            while (c <= 32)
                c = getchar();
            putchar(c);
        }
        puts("");
        return 0;
    }
    newNode();
    for (int i = 0; i < n; i++){
        int c = getchar();
        while (c <= 32)
            c = getchar();
        int p = 0;
        while (c > 32){
            s[p++] = c - 'a';
            c = getchar();
        }
        int v = add(s, k - 1);
        int u = add(s + 1, k - 1);
        edges[v].ptr = pushback(edges[v].ptr, &edges[v].sz, u);
        deg[u]--;
        deg[v]++;
    }
    int from = -1;
    int to   = -1;
    for (int i = 0; i < cn; i++){
        if (deg[i] == 0)
            continue;
        if (deg[i] != 1 && deg[i] != -1){
            puts("-1");
            return 0;
        }
        if ((deg[i] == 1 && from >= 0) || (deg[i] == -1 && to >= 0)) {
            puts("-1");
            return 0;
        }
        if (deg[i] == 1)
            from = i;
        if (deg[i] == -1)
            to = i;
    }
    if (from < 0 && to < 0)
        from = 0;
    dfs(from);
    for (int i = 0; i < cn; i++)
        if (edges[i].sz>0){
            puts("-1");
            return 0;
        }
    for (int i = ac - 1; i >= 0; i--)
        putchar(st[path[i]][0]);
    for (int i = 1; i < k - 1; i++)
        putchar(st[path[0]][i]);
    puts("");
}



































