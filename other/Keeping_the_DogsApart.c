#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef struct{
    double x, y;
}pt;
pt newpt(double x, double y){
    pt rez;
    rez.x = x;
    rez.y = y;
    return rez;
}
bool eq(pt t, pt p){
    return t.x==p.x && t.y==p.y;
}
pt opAdd(pt t, pt p){
    return newpt(t.x+p.x, t.y+p.y);
}
pt opSub(pt t, pt p){
    return newpt(t.x-p.x, t.y-p.y);
}
pt opMul(pt t, double d){
    return newpt(t.x*d, t.y*d);
}
pt opDiv(pt t, double d){
    return newpt(t.x/d, t.y/d);
}
double dot(pt t,pt p){
    return t.x*p.x + t.y*p.y;
}
double dist2(pt t){
    return t.x*t.x + t.y*t.y;
}
double dist(pt t){
    return sqrt(dist2(t));
}
pt unit(pt t){
    if(dist(t) < 1e-9)
        return t;
    return opDiv(t, dist(t));
}
double segDist(pt s, pt e, pt p){
    if(eq(s,e))
        return dist(opSub(p,s));
    double d = dist2(opSub(e,s)),
           t = min(d, max(0., dot(opSub(p,s), opSub(e,s) ) ));
    return dist(opSub(opMul(opSub(p,s),d), opMul(opSub(e,s),t)))/d;
}
int main(){
    int n;
    scanf("%d", &n);
    pt a[n+1];
    for(int i=0; i<n; ++i)
        scanf("%lf %lf", &a[i].x, &a[i].y);
    a[n]=a[n-1];
    int m;
    scanf("%d", &m);
    pt b[m+1];
    for(int i=0; i<m; ++i)
        scanf("%lf %lf", &b[i].x, &b[i].y);
    b[m] = b[m-1];
    pt cura = a[0],
       curb = b[0];
    double ma = dist(opSub(cura, curb));
    int nexta = 1,
        nextb = 1;
    while(nexta < n && nextb < m){
        pt mova = opSub(a[nexta], cura);
        pt movb = opSub(b[nextb], curb);
        double lena = dist(mova);
        double lenb = dist(movb);
        double len = min(lena, lenb);
        pt diff = opSub(cura, curb);
        cura = opAdd(cura, opMul(unit(mova), len));
        curb = opAdd(curb, opMul(unit(movb), len));
        double distance = segDist(diff, opSub(cura, curb), newpt(0, 0));
        ma = min(ma, distance);
        if (lena <= lenb){
            cura = a[nexta];
            nexta++;
        }
        else{
            curb = b[nextb];
            nextb++;
        }
    }
    printf("%.11lf\n", ma);
    return 0;
}
