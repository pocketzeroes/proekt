#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
double EPS = 1e-12;

typedef struct{
    ll x, y;
}pt;
pt newpt(ll x, ll y){
    return(pt){x,y};
}
pt  opAdd(pt t, pt p){
    return newpt(t.x+p.x, t.y+p.y);
}
pt  opSub(pt t, pt p){
    return newpt(t.x-p.x, t.y-p.y);
}
pt  opMul(pt t, ll c){
    return newpt(t.x*c, t.y*c);
}
pt  opDiv(pt t, ll c){
    return newpt(t.x/c, t.y/c);
}
int cmpPt(const void*pa, const void*pb){
    pt*t=(pt*)pa;
    pt*p=(pt*)pb;
    return(t->x<p->x||(t->x==p->x&&t->y<p->y))?-1:1;
}

ll dot(pt p, pt q){
    return p.x*q.x + p.y*q.y;
}
double dist(pt p, pt q){
    return sqrt(dot( opSub(p, q), opSub(p, q) ));
}
ll cross(pt p, pt q){
    return p.x*q.y - p.y*q.x;
}
pt*convex_hull(pt*p, int psz, int*rsz){
    int n = psz,
        k = 0;
    pt*h = calloc(2*n, sizeof(pt));
    qsort(p, psz, sizeof(pt), cmpPt);
    for(int i=0; i<n; i++){
        while(k >= 2 && cross(opSub(h[k-1], h[k-2]), opSub(p[i], h[k-2])) <= 0)
            k--;
        h[k++] = p[i];
    }
    int temp = k+1;
    for(int i=n-2; i>=0; i--){
        while(k >= temp && cross(opSub(h[k-1], h[k-2]), opSub(p[i], h[k-2])) <= 0)
            k--;
        h[k++] = p[i];
    }
   *rsz = k-1;
    return h;
}
int main(){
    int n;
    while(scanf("%d", &n)==1 && n){
        pt*a = calloc(n, sizeof(pt));
        for(int i=0; i<n; i++)
            scanf("%lld %lld", &a[i].x, &a[i].y);
        int hsz;
        pt*h = convex_hull(a, n, &hsz);
        if(hsz == 2 && dist(h[0],h[1]) < EPS){
            h++;
            hsz--;
        }
        if(n == 1){
           h = a;
           hsz = n;
        }
        printf("%d\n", hsz);
        for(int i=0; i<hsz; i++)
            printf("%lld %lld\n", h[i].x, h[i].y);
    }
    return 0;
}
