#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    double x,y;
}pt;
pt newpt(double x, double y){
    return(pt){x,y};
}
double hmax;
double D,L;

pt opadd(pt A, pt B){
    return newpt(A.x+B.x, A.y+B.y);
}
pt opsub(pt A, pt B){
    return newpt(A.x-B.x, A.y-B.y);
}
pt opmul(pt A, double p){
    return newpt(A.x*p, A.y*p);
}
pt opdiv(pt A, double p){
    return newpt(A.x/p, A.y/p);
}
bool oplt(pt a, pt b){
    return a.x<b.x||(a.x==b.x && a.y<b.y);
}
double eps = 1e-8;
int dcmp(double x){
    if(fabs(x)<eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
bool opeq(pt a, pt b){
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
double Dot(pt A, pt B){
    return A.x*B.x+A.y*B.y;
}
double length(pt A){
    return sqrt(Dot(A,A));
}
double Angle(pt A, pt B){
    return acos(Dot(A,B)/length(A)/length(B));
}
double Cross(pt A, pt B){
    return A.x*B.y-B.x*A.y;
}
double Area2(pt A, pt B, pt C){
    return Cross(opsub(B,A), opsub(C,A));
}
double PArea(pt*p, int n){
    double area=0;
    for(int i=0; i<n; i++){
        area+=Cross(p[i],p[(i+1)%n]);
    }
    return fabs(area/2);
}
pt GetLineIntersection(pt P, pt v, pt Q, pt w){
    pt u = opsub(P, Q);
    return opadd(P, opdiv(opmul(v, Cross(w,u)),Cross(v,w)));
}
pt read_point(){
    pt P;
    scanf("%lf %lf", &P.x, &P.y);
    hmax = fmax(hmax, P.y);
    return P;
}
pt get_point(pt a, pt b, double y0){
    if(fabs(a.x - b.x) < eps)
        return newpt(a.x, y0);
    double bi = (y0 - a.y) / (b.y - a.y);
    return newpt(a.x + bi * (b.x - a.x), a.y + bi * (b.y - a.y));
}
int main(){
    pt po[105],Q[105];
    int T,n,q,i;
    while(scanf("%d",&n)!=EOF){
        scanf("%lf%lf",&D,&L);
        hmax=0;
        for(i=0; i<n; i++){
           po[i] = read_point();
        }
        double d=0,h=hmax;
        while(h-d>eps){
            q=0;
            int per=n-1;
            double m=(d+h)/2;
            pt M=newpt(0,m);
            pt w=newpt(1,0);
            for(int i=0; i<n; i++){
                if((m-po[i].y)*(m-po[per].y)<eps){
                    pt PP = opsub(po[i], po[per]);
                    Q[q++]=GetLineIntersection(po[per],PP,M,w);
                }
                if((m-po[i].y)>eps)
                    Q[q++]=po[i];
                per=i;
            }
            double area=PArea(Q,q);
            if(L*1000-area*D>eps)
                d=m;
            else
                h=m;
        }
        printf("%.2f\n",d);
    }
    return 0;
}
