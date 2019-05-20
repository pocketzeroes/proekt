#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
 
 
double R,L,W,Alpha,Beta;
int Case;
 
const double eps=1e-9, inf=10000.0;
 
int sgn(double x){
  if(x<-eps)
    return -1;
  if(x>eps)
    return 1;
  return 0;
}
typedef struct{
  double x,y;
}pt;
pt newpt(double _x, double _y){
  pt rez;
  rez.x = _x;
  rez.y = _y;
  return rez;
}
pt opAdd(pt t, pt v){
  return newpt(t.x+v.x, t.y+v.y);
}
pt opSub(pt t, pt v){
  return newpt(t.x-v.x, t.y-v.y);
}
double opMul(pt t, pt v){
  return t.x*v.x + t.y*v.y;
}
double len(pt t){
  return hypot(t.x, t.y);
}
double cross(pt a, pt b){
  return a.x*b.y-a.y*b.x;
}
double dist_point_to_segment(pt p, pt a, pt b){
  if(sgn(opMul(opSub(p,a),opSub(b,a)))>=0&&sgn(opMul(opSub(p,b),opSub(a,b)))>=0)
    return fabs(cross(opSub(p,a),opSub(b,a)))/len(opSub(b,a));
  return min(len(opSub(p,a)), len(opSub(p,b)));
}
double cal(pt a, pt b, pt c, pt d){
  return min(min(dist_point_to_segment(a, c, d),
                 dist_point_to_segment(b, c, d)),
             min(dist_point_to_segment(c, a, b),
                 dist_point_to_segment(d, a, b)));
}
 
double solve(){
  pt A=newpt(-inf,W), B=newpt(0,W);
  pt D=newpt(L,W),    E=newpt(inf,W);
  pt G=newpt(L,0),    H=newpt(inf,0);
  Alpha=M_PI-Alpha,
  Beta =M_PI-Beta;
  pt C = opAdd(D, newpt(cos(Alpha)*L,sin(Alpha)*L));
  pt F = opAdd(G, newpt(cos(Beta )*L,sin(Beta )*L));
  double ans = min(L,W);
  ans = min(ans, cal(A,B,C,D));
  ans = min(ans, cal(C,D,F,G));
  ans = min(ans, cal(D,E,F,G));
  ans/=2.0;
  ans = min(ans,R);
  ans = max(ans,0.0);
  return ans;
}
int main(){
  scanf("%lf %lf %lf", &R, &L, &W);
  scanf("%d", &Case);
  while(Case--){
    scanf("%lf %lf", &Alpha, &Beta);
    printf("%.9f\n", solve());
  }
  return 0;
}
