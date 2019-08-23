#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}

typedef long long ll;
enum{ maxn =(int) 1e5 + 5};
int N, M, Q;
char*A[maxn];
int sz;
int*nx[maxn];
vec rows;

int next(int i, int j){
    if (A[i][j] == '/') {
        if (j == 1 || A[i][j - 1] == '\\')
            return -1;
        return j - 1;
    }
    else {
        if (j == M || A[i][j + 1] == '/')
            return -1;
        return j + 1;
    }
}
void trau_update(int u, int v, char c){
    A[u][v] = c;
}
int trau_ask(int j){
    int i = 1;
    while (i <= N) {
        int nnx = next(i, j);
        if (nnx == -1)
            return -1;
        j = nnx;
        ++i;
    }
    return j;
}

int  dfs(int i, int j, int mx_row){
    if (i == mx_row) 
        return j;
    if(nx[i][j]) 
        return nx[i][j];
    int p = next(i, j);
    if (p == -1)
        return nx[i][j] = -1;
    return nx[i][j] = dfs(i + 1, p, mx_row);
}
void khong_init(){
    sz = sqrt(M * N);
    sz = (sz + M - 1) / M;
    for (int i = 1; i <= N; i += sz)
        rows.ptr = pushback(rows.ptr, &rows.sz, i);
    rows.ptr = pushback(rows.ptr, &rows.sz, N+1);
    for(int i = 1; i <= N; ++i)
        nx[i]=calloc(M+1, sizeof(int));
    for(int i = 0; i + 1 < rows.sz; ++i)
        for (int j = 1; j <= M; ++j)
            dfs(rows.ptr[i], j, rows.ptr[i + 1]);
}
void khong_update(int u, int v, char c){
    A[u][v] = c;
    int pos = upper_bound(rows.ptr, rows.sz, u) - 1;
    for (int i = rows.ptr[pos]; i < rows.ptr[pos + 1]; ++i)
        for (int j = 1; j <= M; ++j) 
            nx[i][j] = 0;
    for (int j = 1; j <= M; ++j)
        dfs(rows.ptr[pos], j, rows.ptr[pos + 1]);
}
int  khong_ask(int j){
    for (int i = 0; i + 1 < rows.sz; ++i) {
        if (nx[rows.ptr[i]][j] == -1)
            return -1;
        j = nx[rows.ptr[i]][j];
    }
    return j;
}

int main(){
    scanf("%d %d %d", &N, &M, &Q);
    getchar();
    for(int i = 1; i <= N; ++i){
        A[i]=calloc(M+1, sizeof(char));
        for(int j = 1; j <= M; ++j){
            A[i][j]=getchar();
        }
        getchar();
    }
    if(N <= sqrt(100000)){
        while (Q--){
            int typ; 
            scanf("%d", &typ);
            if (typ == 1){
                int x, y;
                scanf("%d %d", &x, &y);
                char c = (A[x][y] == '/' ? '\\' : '/');
                trau_update(x, y, c);
            } 
            else{
                int x;
                scanf("%d", &x);
                printf("%d\n", trau_ask(x));
            }
        }
    } 
    else{
        khong_init();
        while (Q--){
            int typ;
            scanf("%d", &typ);
            if (typ == 1){
                int x, y;
                scanf("%d %d", &x, &y);
                char c = (A[x][y] == '/' ? '\\' : '/');
                khong_update(x, y, c);
            } 
            else {
                int x;
                scanf("%d", &x);
                printf("%d\n", khong_ask(x));
            }
        }
    }
    return 0;
}
