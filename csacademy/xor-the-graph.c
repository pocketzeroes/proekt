#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
///////////////////////////////
enum{ N = (int)1e6 + 3};
int n, m, k;
int ed[N][2];
vec g   [N];
vec odds[N];
int C;
int col    [N];
bool usedEd[N];
int ord    [N];
int sz;
vec  ans   [N];
int ansSz;
bool goodV[N];
bool allOk;

int getOther(int id, int v) {
    return ed[id][0] ^ ed[id][1] ^ v;
}
void addEdge(int v, int u) {
    ed[m][0] = v;
    ed[m][1] = u;
    g[v].ptr = pushback(g[v].ptr, &g[v].sz, m);
    g[u].ptr = pushback(g[u].ptr, &g[u].sz, m);
    m++;
}
void dfs1(int v) {
    col[v] = C;
    allOk &= goodV[v];
    if(g[v].sz & 1)
        odds[C].ptr = pushback(odds[C].ptr, &odds[C].sz, v);
    for(int z=0;z<g[v].sz;z++){int id = g[v].ptr[z];
        int u = getOther(id, v);
        if (col[u] == -1)
            dfs1(u);
    }
}
void dfs2(int v) {
    while(g[v].sz>0) {
        int id = g[v].ptr[g[v].sz-1];
        g[v].sz--;
        if (usedEd[id])
            continue;
        usedEd[id] = 1;
        dfs2(getOther(id, v));
        ord[sz++] = id;
    }
}

void rotate(int array[], int n, int size){
	int *tmp_array = (int*)malloc(n * sizeof(int));
	memcpy(tmp_array, array, n * sizeof(int)); 
	memmove(array, array + n, (size - n) * sizeof(int)); 
	memmove(array + size - n, tmp_array, n * sizeof(int));
	free(tmp_array);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int v = 0; v < n; v++)
        goodV[v] = 1;
    m = 0;
    while(k--) {
        int v, u, w;
        scanf("%d%d%d", &v, &u, &w);
        v--;u--;
        if (w == 1) {
            goodV[v] = goodV[u] = 0;
        }
        for (int i = 0; i < 2 + w; i++)
            addEdge(v, u);
    }
    for (int i = 0; i < n; i++)
        col[i] = -1;
    for (int v = 0; v < n; v++) {
        if (col[v] != -1 || g[v].sz==0)
            continue;
        allOk = true;
        dfs1(v);
        if (allOk) {
            continue;
        }
        if (odds[C].sz==0) {
            odds[C].ptr = pushback(odds[C].ptr, &odds[C].sz, v);
            odds[C].ptr = pushback(odds[C].ptr, &odds[C].sz, v);
        }
        C++;
    }
    if(C == 0){
        printf("0\n");
        return 0;
    }
    k = m;
    if (C != 1) {
        for (int i = 0; i < C - 1; i++){
            int v = odds[i].ptr[odds[i].sz-1];
            odds[i].sz--;
            int u = odds[i+1].ptr[odds[i+1].sz-1];
            odds[i + 1].sz--;
            addEdge(v, u);
        }
    }
    int lst = -1;
    for (int i = 0; i < C; i++)
        for(int z=0;z<odds[i].sz;z++){int v = odds[i].ptr[z];
            if (lst == -1)
                lst = v;
            else {
                addEdge(lst, v);
                lst = -1;
            }
        }
    if(lst != -1)
        assert(!"throw");
    lst = 0;
    while(goodV[lst])
        lst++;
    dfs2(lst);
    if (k != m) {
        int pos = 0;
        while(ord[pos] < k) {
            lst = getOther(ord[pos], lst);
            pos++;
        }
        lst = getOther(ord[pos], lst);
        pos++;
        rotate(ord, pos, sz);
    }
    printf("%d\n", max(1, m - k));
    ans[ansSz].ptr = pushback(ans[ansSz].ptr, &ans[ansSz].sz, lst+1);
    for(int i = 0; i < sz; i++){
        int id = ord[i];
        lst = getOther(id, lst);
        if (id >= k)
            ansSz++;
        ans[ansSz].ptr = pushback(ans[ansSz].ptr, &ans[ansSz].sz, lst+1);
    }
    ansSz = max(1, m - k);
    for (int i = 0; i < ansSz; i++){
        printf("%d ", ans[i].sz);
        for(int q=0;q<ans[i].sz;q++){int v = ans[i].ptr[q];
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}
