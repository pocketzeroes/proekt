#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>

typedef struct{
  double x, y;
}pt;
pt newpt(double a, double b){
  return(pt){a,b};
}
pt sub(pt P, pt Q){
  return newpt(P.x-Q.x, P.y-Q.y);
}
pt add(pt t, pt p){
    return newpt(t.x+p.x, t.y+p.y);
}
pt mul(pt t, double d){
    return newpt(t.x*d, t.y*d);
}
double opmul(pt t, pt s){
    return t.x*s.x+t.y*s.y;
}
double dot(pt P, pt Q){
  return P.x*Q.x + P.y*Q.y;
}
double cross(pt P, pt Q){
  return P.x*Q.y - P.y*Q.x;
}
bool equ(pt t, pt p){
    return t.x==p.x && t.y==p.y;
}
double len(pt a){
    return sqrt(opmul(a, a));
}

typedef struct{
  pt a, b;
}Line;
Line newLine(pt a, pt b){
  return(Line){a,b};
}
pt Point_ZERO;
/////////////////////////////

double distanceToPoint(Line t, pt p){//puts(__FUNCTION__);
    pt a = t.a;
    pt b = t.b;
    pt d = sub(b, a);
    if(equ(d, Point_ZERO))
        return len(sub(p, a));
    double x = dot(sub(p, a), d) / dot(d, d);
    if(x < 0.0)
        return len(sub(p, a));
    else if(x > 1.0)
        return len(sub(p, b));
    else
        return len(sub(p, add(a, mul(d, x))));
}
bool doesIntersect(Line t, Line l){//puts(__FUNCTION__);
    pt a = t.a;
    pt b = t.b;
    pt c = l.a;
    pt d = l.b;
    pt e = sub(b, a);
    pt f = sub(d, c);
    double x = cross(f, e);
    if(x == 0.0)
        return false;
    double y = (e.x * (c.y - a.y) + e.y * (a.x - c.x)) / x;
    double z = (f.x * (a.y - c.y) + f.y * (c.x - a.x)) /-x;
    return 0.0 <= y && y <= 1.0 && 0.0 <= z && z <= 1.0;
}
double distanceToLineSegment(Line t, Line l){//puts(__FUNCTION__);
    pt a = t.a;
    pt b = t.b;
    pt c = l.a;
    pt d = l.b;
    if(doesIntersect(t, l))
        return 0.0;
    double distances[4];
    distances[0] = distanceToPoint(t, c);
    distances[1] = distanceToPoint(t, d);
    distances[2] = distanceToPoint(l, a);
    distances[3] = distanceToPoint(l, b);
    double min = DBL_MAX;
    for(int z=0;z<4;z++){double dist = distances[z];
        if(dist < min)
           min = dist;
    }
    return min;
}
int main(){//puts(__FUNCTION__);
  double x1, y1, x2, y2, x3, y3, x4, y4;
  int n;
  scanf("%d", &n);
  for(int z=0; z<n; z++){
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4); // puts("opa");
    pt a = newpt(x1, y1);                                                             // puts("opa");
    pt b = newpt(x2, y2);                                                             // puts("opa");
    Line l1 = newLine(a, b);                                                          // puts("opa");
    pt c = newpt(x3, y3);                                                             // puts("opa");
    pt d = newpt(x4, y4);                                                             // puts("opa");
    Line l2 = newLine(c, d);                                                          // puts("opa");
//   puts("hi");                                                                       // puts("opa");
    printf("%.2lf\n", distanceToLineSegment(l1, l2));
  }
  return 0;
}
