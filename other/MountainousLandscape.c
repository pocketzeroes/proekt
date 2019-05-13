#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef struct{
    int x, y;
}point;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
point*pushbackPt(point*array, int *size, point value){
    point*output = resizeArray(array, point, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	point*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

point opSub(point p, point q){
    point r;
    r.x = p.x - q.x;
    r.y = p.y - q.y;
    return r;
}
ll opMul(point p, point q){
    return 1LL*p.x*q.y - 1LL*p.y*q.x;
}
    
void build(vecpt*T, int i, int l, int r, point*P){
    if (l >= r)
        return;
    vecpt*H = &T[i];
    for (int j=l; j<=r; ++j){
        while(H->sz > 1 && opMul(opSub(P[j], H->ptr[H->sz-2]), opSub(H->ptr[H->sz-1], H->ptr[H->sz-2])) <= 0)
            H->sz--;
        H->ptr = pushbackPt(H->ptr, &H->sz, P[j]);
    }
    if (r-l > 1){
        build(T, 2*i+0, l, (l+r)/2, P);
        build(T, 2*i+1, (l+r)/2, r, P);
    }
}
bool cuts(point p, point q, vecpt r){
    int lo = 0, 
        hi = r.sz - 2;
    while (lo < hi){
        int me = (lo + hi) / 2;
        if(opMul(opSub(r.ptr[me],p), opSub(q, p)) < opMul(opSub(r.ptr[me+1],p), opSub(q,p)))
            hi = me;
        else
            lo = me+1;
    }
    return(opMul(opSub(r.ptr[lo  ],p),opSub(q,p)) < 0)||
          (opMul(opSub(r.ptr[lo+1],p),opSub(q,p)) < 0);
}
bool lookup(vecpt*T, int i, int l, int r, point p, point q, int b, int e, int*w){
    if (e <= l || r <= b)
        return false;
    if (b <= l && r <= e){
        if (!cuts(p, q, T[i]))
            return false;
        if (r-l == 1){
           *w = l;
            return true;
        }
    }
    return lookup(T, 2*i+0, l, (l+r)/2, p, q, b, e, w) || 
           lookup(T, 2*i+1, (l+r)/2, r, p, q, b, e, w);
}
void testcase(){
    int n;
    scanf("%d", &n);
    point P[n];
    for(int i=0; i<n; i++)
        scanf("%d %d", &P[i].x, &P[i].y);
    vecpt T[4*n]; memset(T, 0, sizeof(T));
    build(T, 1, 0, n-1, P);
    for(int i=0; i<n-2; ++i){
        if(opMul(opSub(P[i+2],P[i]),opSub(P[i+1],P[i]))<0)
            printf("%d ", i+2);
        else{
            int w = -1;
            lookup(T, 1, 0, n-1, P[i], P[i+1], i+2, n-1, &w);
            printf("%d ", w+1);
        }
    }
    puts("0");
}
int main(){
    int z;
    scanf("%d", &z);
    for(int q=0; q<z; q++)
        testcase();
    return 0;
}
