#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

#define inf 1000000000000
#define M 100009
#define eps 1e-12

typedef struct{
    double x, y;
}pt;
pt p[M];

pt newpt(double x, double y){
    return(pt){x, y};
}
pt opsub(pt t, pt s){
    return newpt(t.x-s.x,t.y-s.y);
}
pt opadd(pt t, pt s){
    return newpt(t.x+s.x,t.y+s.y);
}
double opmul(pt t, pt s){
    return t.x*s.x+t.y*s.y;
}
double opxor(pt t, pt s){
    return t.x*s.y-t.y*s.x;
}

double len(pt a){
    return sqrt(opmul(a,a));
}
double dis(pt a, pt b){
    return len(opsub(b,a));
}
double cross(pt a, pt b, pt c){
    return opxor(opsub(b,a),opsub(c,a));
}
double dot(pt a, pt b, pt c){
    return opmul(opsub(b,a) , opsub(c,a));
}
int judge(pt a, pt b, pt c){
    if (c.x>=fmin(a.x,b.x) &&c.x<=fmax(a.x,b.x) &&c.y>=fmin(a.y,b.y) &&c.y<=fmax(a.y,b.y))
        return 1;
    return 0;
}
double area(pt b, pt c, double r){
    pt a=newpt(0.0,0.0);
    if(dis(b,c)<eps)
        return 0.0;
    double h=fabs(cross(a,b,c))/dis(b,c);
    if(dis(a,b)>r-eps&&dis(a,c)>r-eps){
        double angle=acos(dot(a,b,c)/dis(a,b)/dis(a,c));
        if(h>r-eps)
            return 0.5*r*r*angle;
        else if(dot(b,a,c)>0&&dot(c,a,b)>0){
            double angle1=2*acos(h/r);
            return 0.5*r*r*fabs(angle-angle1)+0.5*r*r*sin(angle1);
        }
        else
            return 0.5*r*r*angle;
    }
    else if(dis(a,b)<r+eps&&dis(a,c)<r+eps)
        return 0.5*fabs(cross(a,b,c));
    else{
        if(dis(a,b)>dis(a,c))
            swap(b,c);
        if(fabs(dis(a,b))<eps)
            return 0.0;
        if(dot(b,a,c)<eps){
            double angle1=acos(h/dis(a,b));
            double angle2=acos(h/r)-angle1;
            double angle3=acos(h/dis(a,c))-acos(h/r);
            return 0.5*dis(a,b)*r*sin(angle2)+0.5*r*r*angle3;
        }
        else{
            double angle1=acos(h/dis(a,b));
            double angle2=acos(h/r);
            double angle3=acos(h/dis(a,c))-angle2;
            return 0.5*r*dis(a,b)*sin(angle1+angle2)+0.5*r*r*angle3;
        }
    }
}
int main(){
    int n;
    double R;
    scanf("%d %lf", &n, &R);
    for(int i=1; i<=n; i++)
        scanf("%lf %lf", &p[i].x, &p[i].y);
    p[n+1]=p[1];
    pt O=newpt(0,0);
    for(int i=1; i<=n+1; i++)
        p[i] = opsub(p[i], O);
    O = newpt(0,0);
    double sum=0;
    for(int i=1; i<=n; i++){
        int j=i+1;
        double s = area(p[i], p[j], R);
        if(cross(O,p[i], p[j])>0)
            sum+=s;
        else
            sum-=s;
    }
    printf("%.12lf\n", fabs(sum));
    return 0;
}
