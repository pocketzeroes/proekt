#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

typedef struct{
  double x,y;
}pt;
pt newpt(double x, double y){
  pt rez;
  rez.x = x;
  rez.y = y;
  return rez;
}
pt minus(pt p, pt a){
  return newpt(p.x-a.x, p.y-a.y);
}
double mag(pt p){
  return sqrt(p.x*p.x + p.y*p.y);
}
pt scale(pt p, double s){
  return newpt(s*p.x, s*p.y);
}
inline double dot(pt p, pt a){
  return p.x*a.x + p.y*a.y;
}
inline double round(double d){
  return ((int)(d*100+.5))/100.0;
}
bool collide(pt a, pt b, pt c, float r){
  c = minus(c, a);
  b = minus(b, a);
  pt proj = scale(b, dot(b, c)/dot(b, b));
  if(dot(proj, b) < 0)
    return false;
  if(dot(minus(b, proj), b) < 0)
    return false;
  return(mag(minus(c, proj)) < 2*r);
}
int main(){
  int w  = in_nextInt();
  int l  = in_nextInt();
  int r  = in_nextInt();
  int x1 = in_nextInt();
  int y1 = in_nextInt();
  int x2 = in_nextInt();
  int y2 = in_nextInt();
  int x3 = in_nextInt();
  int y3 = in_nextInt();
  int h  = in_nextInt();
  pt left  = newpt(0,l);
  pt right = newpt(w,l);
  pt b1    = newpt(x1,y1);
  pt b2    = newpt(x2,y2);
  pt b3    = newpt(x3,y3);
  pt temp      = minus(right, b3);
  pt t3        = minus(b3, scale(temp, 2*r/mag(temp)));
  temp         = minus(left, b2);
  pt t2        = minus(b2, scale(temp, 2*r/mag(temp)));
  temp         = minus(t3, b1);
  pt t1        = minus(b1, scale(temp, 2*r/mag(temp)));
  pt mir       = minus(t3, b1);
  pt ref       = minus(t2, t1);
  pt result    = minus(scale(mir, 2*dot(mir, ref) / dot(mir, mir)), ref);
  result       = scale(result, 1/mag(result));
  double x     = t1.x - (t1.y-h)/result.y*result.x;
  double theta = 180+180/M_PI*atan2(result.y,result.x);
  pt cue       = newpt(x,h);
  if(x < r || x > w-r)                                      puts("impossible");
  else if(dot(minus(result, t1), minus(b1, t1)) >= 0)       puts("impossible");
  else if(dot(minus(t1, t2), minus(b2, t2)) >= 0)           puts("impossible");
  else if(dot(minus(b1,t3), minus(b3, t3)) >= 0)            puts("impossible");
  else if(collide(cue, t1, b2, r))                          puts("impossible");
  else if(collide(cue, t1, b3, r))                          puts("impossible");
  else if(collide(t1, t2, b3, r))                           puts("impossible");
  else if(collide(b1, t3, b2, r))                           puts("impossible");
  else if(t1.x < r || t1.x > w-r || t1.y < r || t1.y > l-r) puts("impossible");
  else if(t2.x < r || t2.x > w-r || t2.y < r || t2.y > l-r) puts("impossible");
  else if(t3.x < r || t3.x > w-r || t3.y < r || t3.y > l-r) puts("impossible");
  else
    printf("%.02lf %.02lf\n", x, theta);
  return 0;
}
