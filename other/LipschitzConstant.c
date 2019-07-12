#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
typedef struct{
    double x, y;
}pair;
pair a[200222];
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  return(a->x < b->x)?-1:1;
}
int main(){
    int i,j,k;
    double p,q,r;
    double t = -1.0;
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        scanf("%lf %lf",&a[i].x,&a[i].y);
    }
    qsort(a, n, sizeof(pair), cmpP);
    for(i=0;i<n-1;i++) {
        p = a[i+1].x - a[i].x;
        q = a[i+1].y - a[i].y;
        if(p < 0.0) p *= -1.0;
        if(q < 0.0) q *= -1.0;
        r = q/p;
        if(r > t) t = r;
    }
    printf("%lf",t);
    return 0;
}
