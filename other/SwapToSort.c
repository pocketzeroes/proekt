#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
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
bool is_sorted(int*a, int asz){
  for(int i=1; i<asz; i++)
    if(a[i-1] > a[i])
      return 0;
  return 1;
}
//////////////////////////////////
enum{MAXN =(int)1e6 + 5};
int N, K, A[MAXN], UF[MAXN];
vec val[MAXN], ind[MAXN];

int find(int v){
    if(UF[v]<0)
        return v;
    else
        UF[v] = find(UF[v]);
    return UF[v];
}
void join(int v, int w){
    v = find(v),
    w = find(w);
    if(v == w)
        return;
    if(UF[v] > UF[w])
        swap(v, w);
    UF[v] += UF[w];
    UF[w] = v;
}
int main(){
    scanf("%d %d", &N, &K);
    for(int i=0; i<N; UF[i++] = -1)
        A[i] = N - i;
    for(int i=0,a,b; i<K; i++){
        scanf("%d %d", &a, &b);
        join(--a, --b);
    }
    for(int i=0; i<N; i++){
       int fi = find(i);
       pb(val[fi], A[i]);
       pb(ind[fi], i);
    }
    for(int i=0; i<N; i++)
        qsort(val[i].ptr, val[i].sz, sizeof(int), cmp);
    for(int i=0; i<N; i++)
        for(int j=0; j<val[i].sz; j++)
            A[ind[i].ptr[j]] = val[i].ptr[j];
    puts(is_sorted(A, N) ? "Yes" : "No");
    return 0;
}
