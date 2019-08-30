#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

const double eps=1e-8;
enum{ N=10000};
int sgn(double x){
  if(x<-eps)return -1;
  if(x>eps)return 1;
  return 0;
}
typedef struct{
  double x,y;
}pt;
pt newpt(double x, double y){
  return(pt){x,y};
}
pt opAdd(pt t, pt v){
  return newpt(t.x+v.x, t.y+v.y);
}
pt opSub(pt t, pt v){
  return newpt(t.x-v.x, t.y-v.y);
}
pt opMul2(pt p, double v){
  return newpt(p.x*v, p.y*v);
}
pt opDiv(pt p,double v){
  return newpt(p.x/v, p.y/v);
}
double opMul(pt p, pt v){
  return p.x*v.x + p.y*v.y;
}
double len(pt p){
  return hypot(p.x, p.y);
}
pt a[N],q[N];
int n,m,i,j;
double cross(pt a,pt b){
  return a.x*b.y-a.y*b.x;
}
double dist_point_to_line(pt p, pt a, pt b){
  return fabs(cross(opSub(p,a), opSub(b,a))) / len(opSub(b,a));
}
double dist_point_to_segment(pt p, pt a, pt b){
  if(sgn(opMul(opSub(p, a), opSub(b,a))) >=0 && sgn(opMul(opSub(p,b), opSub(a,b)))>=0)
    return fabs(cross( opSub(p,a), opSub(b,a)))/len(opSub(b,a));
  return fmin(len(opSub(p,a)),len(opSub(p,b)));
}
void solve(pt A, pt B, pt C){
  if(cross(opSub(A,B), opSub(C,B))<0)
    return;
  pt D = opSub(A, B);
  D    = opDiv(D, len(D));
  D    = opAdd(D, B);
  pt E = opSub(C, B);
  E    = opDiv(E, len(E));
  E    = opAdd(E, B);
  pt F = opDiv(opAdd(D, E), 2.0);
  F    = opSub(F, B);
  F    = opDiv(F, len(F));
  double l=0,
         r=1e8,
         mid;
  while(l+eps<r){
    mid=(l+r)/2.0;
    if(dist_point_to_line(opAdd(B, opMul2(F, mid)), A, B)<4000.1)
      l=mid;
    else 
      r=mid;
  }
  pt o = opAdd(B, opMul2(F, l));
  for(int i=0;i<n;i++){
    if(sgn(dist_point_to_segment(o, a[i], a[i+1])-4000.0)<=0)
      return;
  }
  q[++m]=o;
}
inline bool check(pt a,pt b){
  return sgn(len(opSub(a,b))-8000.1)>=0;
}
int main(){
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%lf%lf", &a[i].x, &a[i].y);
    a[i+n]=a[i];
  }
  for(i=0;i<n;i++)
    solve(a[i],a[i+1],a[i+2]);
  for(i=1;i<=m;i++)
    for(j=1;j<i;j++)
      if(check(q[i],q[j])){
        printf("%.8f %.8f\n",q[i].x,q[i].y);
        printf("%.8f %.8f\n",q[j].x,q[j].y);
        return 0;
      }
  puts("impossible");
  return 0;
}
