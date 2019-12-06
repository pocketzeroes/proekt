#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define back(vv) vv.ptr[vv.sz-1]
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

enum{ N =(int)1e3 + 10};
enum{ dim = 3         };
int S[dim], n;
int c[N][dim];
int a[N][dim << 1];
int p[N];

int*newpair(int a, int b){
  int*rez = calloc(2, sizeof(int));
  rez[0] = a;
  rez[1] = b;
  return rez;
}
#define pbp(zpv, zvv) zpv->ptr = pushbackP(zpv->ptr, &zpv->sz, zvv)
int**pushbackP(int**array, int*size, int*value){
  int**output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int**ptr;
	int sz;
}vecp;
vecp newvecp(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////


int comp(const void*pa, const void*pb){
    int*aa=(int*)pa;
    int*bb=(int*)pb;
    int i= *aa;
    int j= *bb;
    for(int k=0; k<dim; k++)
        if(c[i][k] != c[j][k])
            return(c[i][k] < c[j][k])?-1:1;
    return 1;
}
void DFS(vecp*coor, int L, int R, int lv){
    if(lv == dim){
        int pos = p[L];
        for(int i=0; i<dim; i++)
            for(int j=0; j<2; j++)
                a[pos][j * dim + i] = coor->ptr[i][j];
        return;
    }
    vec need = newVec();
    pb(need, c[p[L]][lv]);
    for(int i=L; i<R; i++){
        int cur = p[i];
        if(c[cur][lv] != back(need))
            pb(need, c[cur][lv]);
    }
    pb(need, S[lv]+1);
    need.ptr[0] = 1;
    for(int mid=0, nL=L; mid<need.sz-1; mid++){
        int nR = nL;
        pbp(coor, newpair(need.ptr[mid], need.ptr[mid + 1]-1));
        while(nR < R){
            int cur = p[nR];
            if(c[cur][lv] <= coor->ptr[lv][1])
                nR++;
            else
                break;
        }
        DFS(coor, nL, nR, lv + 1);
        coor->sz--;
        nL = nR;
    }
}
void solve(){
    vecp coor = newvecp();
    DFS(&coor, 0, n, 0);
    puts("YES");
    for(int i=0; i<n; i++){
        for(int j=0; j<2*dim ; j++)
            printf("%d ", a[i][j]);
        puts("");
    }
}
int main(){
    while(1){
        for(int i=0; i<dim; i++)
            if(scanf("%d", &S[i])!=1)
                return 0;
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            for(int j=0; j<dim; j++)
                scanf("%d", &c[i][j]);
        for(int i=0; i<n; i++)
            p[i] = i;
        qsort(p, n, sizeof(int), comp);
        solve();
    }
    return 0;
}
