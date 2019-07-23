#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef long long ll;

int L, W;
double X, Y, Ws;
bool conn[433][433];

typedef struct{
  double x, y;
}vect;
vect newvect(double _x, double _y){
  vect rez;
  rez.x = _x; 
  rez.y = _y;
  return rez;
}
typedef struct{
  double x, y;
  char*naam;
}pt;
pt newpt(double _x, double _y, char*_n){
  pt rez;
  rez.x   = _x;
  rez.y   = _y;
  rez.naam = strdup(_n);
  return rez;
}

vect opSub(pt p, pt q){
  return newvect(q.x-p.x, q.y-p.y);
}
double cross(vect u, vect v){
  return u.x*v.y - u.y*v.x; 
}
int sgn(double i){
  return (i > 0) ? 1 : ((i < 0) ? -1 : 0);
}
int direction (pt a, pt b, pt c) {
  return sgn(cross(opSub(b,a), opSub(c,a)));
}

bool onSegment(pt a, pt b, pt c) {
  return (min(a.x, b.x) <= c.x && max(a.x, b.x) >= c.x && min(a.y, b.y) <= c.y && max(a.y, b.y) >= c.y);
}
bool segIntersect (pt p1, pt p2, pt p3, pt p4){
  int d1 = direction(p3, p4, p1);
  int d2 = direction(p3, p4, p2);
  int d3 = direction(p1, p2, p3);
  int d4 = direction(p1, p2, p4);
  if (d1*d2 < 0 && d3*d4 < 0)
    return true;
  if (d1 == 0 && onSegment(p3,p4,p1))
    return true;
  if (d2 == 0 && onSegment(p3,p4,p2))
    return true;
  if (d3 == 0 && onSegment(p1,p2,p3))
    return true;
  if (d4 == 0 && onSegment(p1,p2,p4))
    return true;
  return false;
}
pt P[433];
pt LB, LO, RB, RO;
int aP;

void doit(){
  aP = 0;
  scanf("%d %d %lf %lf %lf", &L, &W, &X, &Y, &Ws);
  LO = newpt(X,Y,"doos");
  LB = newpt(X,Y+Ws,"doos");
  RO = newpt(X+Ws,Y,"doos");
  RB = newpt(X+Ws,Y+Ws,"doos");
  for (int i = 0; i <= W; i++) {
    P[aP] = newpt(0,i,"pannenkoek"); aP++;
    P[aP] = newpt(L,i,"pannenkoek"); aP++;
  }
  for (int j = 1; j < L; j++) {
    P[aP] = newpt(j,0,"pannenkoek"); aP++;
    P[aP] = newpt(j,W,"pannenkoek"); aP++;
  }
  for (int i = 0; i < aP; i++){
    for (int j = 0; j < aP; j++){
      if (i == j)
        conn[i][j] = false;
      else
        conn[i][j] = !(segIntersect(LO,RB,P[i],P[j]) || segIntersect(RO,LB,P[i],P[j]));
    }
  }
  ll sol = - W*(W+1)*(W-1)/3 - L*(L+1)*(L-1)/3;
  for (int i = 0; i < aP; i++)
  for (int j = i+1; j < aP; j++)
  for (int k = j+1; k < aP; k++) {
    if (conn[i][j] && conn[j][k] && conn[i][k])
      sol++;
  }
  printf("%lld\n", sol);
}
int main(){
  int T;
  scanf("%d", &T);
  for(int t=1; t<=T; t++)
    doit();
  return 0;
}
