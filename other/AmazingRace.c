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
int cmpVec(vec*a, vec*b){
  int msz = fmin(a->sz, b->sz);
  for(int i=0;i < msz; i++){
    if(a->ptr[i] != b->ptr[i]) 
        return (a->ptr[i] < b->ptr[i])?-1:1;
  }
  if(a->sz!=b->sz)
      return (a->sz < b->sz)?-1:1;
  return 0;
}
/////////////////////////////
const double oo = 1<<20;
int mint[1<<20][22],
    back[1<<20][22];
int n, T, p[30], t[30], d[30], A[30][30];

int MinT(int S, int at){
    if (S & (1<<at)){
        int r = MinT(S & ~(1<<at), at);
        return (r <= d[at]-t[at]) ? r + t[at] : oo;
    }
    if (!S)
        return A[n][at];
#define r mint[S][at]
    if (r == -1){
        r = oo;
        for(int i = 0; i < n; ++i)
            if(S & (1<<i))
                r = fmin(r, MinT(S, i) + A[i][at]);
    }
    return r;
    #undef r
}
int main(){
    scanf("%d %d", &n, &T);
    for (int i = 0; i < n; ++i){
        scanf("%d %d %d", p+i, t+i, d+i);
        if (d[i] < 0)
            d[i] = oo;
    }
    for (int i = 0; i < n+2; ++i)
        for (int j = 0; j < n+2; ++j)
            scanf("%d", A[i]+j);
    int ans = 0;
    vec best = newVec();
    memset(mint, -1, sizeof(mint));
    for (int S = 0; S < (1<<n); ++S) {
        if (MinT(S, n+1) <= T) {
            int v = 0;
            vec vis=newVec();
            for (int i = 0; i < n; ++i){
                if (S & (1<<i)){
                    v += p[i];
                    vis.ptr = pushback(vis.ptr, &vis.sz, i+1);
                }
            }
            if(v > ans || v == ans && cmpVec(&vis, &best)<0){
                ans = v;
                if(best.ptr)free(best.ptr);  // copyVec
                best.sz = vis.sz;
                best.ptr = calloc(vis.sz, sizeof(int));
                for(int i=0; i<vis.sz; i++)
                    best.ptr[i] = vis.ptr[i];
            }
        }
    }
    printf("%d\n", ans);
    for (int i = 0; i < best.sz; ++i)
        printf("%d%c", best.ptr[i], i==best.sz-1 ? '\n' : ' ');
    return 0;
}
