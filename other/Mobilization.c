#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  double x, y;
}pt;
pt newpt(double a, double b){
  return(pt){a,b};
}
#define pb(zpv, zvv) zpv.ptr = pushbackPt(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pt*pushbackPt(pt*array, int *size, pt value){
   pt*output = resizeArray(array, pt, *size + 1);
   output[(*size)++] = value;
   return output;
}
typedef struct{
	pt*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpPt(const void*pa, const void*pb){
  pt*a = (pt*)pa;
  pt*b = (pt*)pb;
  if(a->x != b->x)return(a->x < b->x)?-1:1;
  if(a->y != b->y)return(a->y < b->y)?-1:1;
  return 0;
}
///////////////////

bool interplow(pt a, pt b, pt c){
   double delta = c.x - a.x;
   if(delta == 0)
      return b.y < a.y || b.y < c.y;
   double y = (a.y * (c.x - b.x) + c.y * (b.x - a.x)) / delta;
   return b.y < y;
}
int main(){
   int N;
   double budget;
   scanf("%d %lf", &N, &budget);
   vecpt pts=newVecPt();
   pb(pts, newpt(0, 0));
   for(int i=0; i<N; i++){
      double cost, health, potency;
      scanf("%lf%lf%lf", &cost, &health, &potency);
      pb(pts, newpt(budget*health/cost, budget*potency/cost));
   }
   qsort(pts.ptr, pts.sz, sizeof(pt), cmpPt);
   double r=0.;
   for(int i=1; i<pts.sz; i++)
      r = fmax(pts.ptr[i].x*pts.ptr[i].y, r);
   int wr=1;
   for(int i=1; i<pts.sz; i++){
      while(wr > 1 && interplow(pts.ptr[wr-2], pts.ptr[wr-1], pts.ptr[i]))
         wr--;
      pts.ptr[wr++] = pts.ptr[i];
   }
   for(int i=1; i+1<wr; i++){
      double a = pts.ptr[i+1].y - pts.ptr[i].y;
      double b = pts.ptr[i].x - pts.ptr[i+1].x;
      double c = a * pts.ptr[i].x + b * pts.ptr[i].y;
      if(a != 0){
         double bx = c / (2*a);
         if(bx > pts.ptr[i].x && bx < pts.ptr[i+1].x){
            double by = (c - a * bx) / b;
            r = fmax(r, bx*by);
         }
      }
   }
   printf("%.2lf\n", r);
   return 0;
}
