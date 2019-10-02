#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>
#define pb(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
typedef double dbl;
dbl in_nextDouble(){
  dbl xx;
  scanf("%lf", &xx);
  return xx;
}
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

///////////////////

typedef struct pt{  //point
   double x, y;
}pt;
pt newpt(double x, double y){
   return(pt){x,y};
}
pt add(pt lhs, pt rhs){
   return newpt(lhs.x+rhs.x, lhs.y+rhs.y);
}
pt sub(pt lhs, pt rhs){
   return newpt(lhs.x-rhs.x, lhs.y-rhs.y);
}
pt midpt(pt lhs, pt rhs){
   return newpt(0.5*(lhs.x+rhs.x), 0.5*(lhs.y+rhs.y));
}
pt scale(pt lhs, double s){
   return newpt(lhs.x*s, lhs.y*s);
}
double cross(pt lhs, pt rhs){
   return lhs.x*rhs.y - lhs.y*rhs.x;
}
pt NIL={-DBL_MAX, -DBL_MAX};

typedef struct line{ // line
   pt a, b;
}line;
line newline(pt a, pt b){
   return(line){a,b};
}
pt getVec2(line l){
   return sub(l.b, l.a);
}
int getSide(line l, pt p){
   pt v1 = getVec2(l), 
      v2 = sub(p, l.a);
   return cross(v1, v2) > 0 ? 0 : 1;
}
pt midpoint(line l){
   return midpt(l.a, l.b);
}
pt intersect(line lhs, line rhs){
   pt v1 = getVec2(lhs),
      v2 = getVec2(rhs),
      v3 = sub(rhs.a, lhs.a);
   double div = cross(v1, v2), 
          sn  = cross(v3, v2);
   if(fabs(div) < 1e-9)
      return NIL;
   double s = sn/div;
   pt p = add(scale(v1, s), lhs.a);
   double ZERO = 1e-9, 
          ONE  = 1-1e-9;
   if(s < ZERO || s > ONE)
      return NIL;
   return p;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
line*pushbackL(line*array, int *size, line value){
  line*output = resizeArray(array, line, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	line*ptr;
	int sz;
}vecl;
vecl newVecL(){
	vecl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////////////////
typedef struct Polygon{//poly
   vecl lines;//of line
}Polygon;

Polygon newPolygon(int N){
   Polygon tva;
   tva.lines = newVecL();//of line
   pt pts[N];
   for(int i=0; i<N; i++){
      double px = in_nextDouble();
      double py = in_nextDouble();
      pts[i] = newpt(px, py);
   }
   for(int i=0; i<N; i++)
      pb(tva.lines, newline(pts[i], pts[(i+1)%N]));
   return tva;
}
Polygon newPoly(){
   Polygon tva;
   tva.lines = newVecL();//of line
   return tva;
}
double getMinX(Polygon*p){
   double minX = DBL_MAX;
   for(int z=0;z<p->lines.sz;z++){line L = p->lines.ptr[z];
      minX = fmin(minX, fmin(L.a.x, L.b.x));
   }
   return minX;
}
double getMinY(Polygon*p){
   double minY = DBL_MAX;
   for(int z=0;z<p->lines.sz;z++){line L = p->lines.ptr[z];
      minY = fmin(minY, fmin(L.a.y, L.b.y));
   }
   return minY;
}
double getMaxX(Polygon*p){
   double maxX = DBL_MIN;
   for(int z=0;z<p->lines.sz;z++){line L = p->lines.ptr[z];
      maxX = fmax(maxX, fmax(L.a.x, L.b.x));
   }
   return maxX;
}
double getMaxY(Polygon*p){
   double maxY = DBL_MIN;
   for(int z=0;z<p->lines.sz;z++){line L = p->lines.ptr[z];
      maxY = fmax(maxY, fmax(L.a.y, L.b.y));
   }
   return maxY;
}
Polygon*split(Polygon*p, line splitLine){
   Polygon*res = calloc(2, sizeof(Polygon));
   for(int z=0;z<p->lines.sz;z++){line cur = p->lines.ptr[z];
      pt p = intersect(cur, splitLine);
      if(p.x == -DBL_MAX){
         pt m = midpoint(cur);
         pb(res[getSide(splitLine, m)].lines, cur);
      }
      else{
         int s1 = getSide(splitLine, cur.a);
         int s2 = getSide(splitLine, cur.b);
         if(s1 == s2)
            fprintf(stderr, "BADNESS! Split failed! %s to %s%n", splitLine, cur);
         pb(res[s1].lines, newline(cur.a, p));
         pb(res[s2].lines, newline(cur.b, p));
      }
   }
   return res;
}
Polygon merge(Polygon*lhs, Polygon*rhs){
   Polygon res = newPoly();
   for(int z=0;z<lhs->lines.sz;z++){line L = lhs->lines.ptr[z];
      pb(res.lines, L);
   }
   for(int z=0;z<rhs->lines.sz;z++){line L = rhs->lines.ptr[z];
      pb(res.lines, L);
   }
   return res;
}
Polygon clipLowLeft (Polygon*p, double sideLen){
   double y = getMinY(p)+sideLen;
   line splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*sides = split(p, splitLine);
   double x = getMinX(&sides[1])+sideLen;
   splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*spl=split(&sides[1], splitLine);
   return merge(&sides[0], &spl[1]);
}
Polygon clipLowRight(Polygon*p, double sideLen){
   double y = getMinY(p)+sideLen;
   line splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*sides = split(p, splitLine);
   double x = getMaxX(&sides[1])-sideLen;
   splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*spl=split(&sides[1], splitLine);
   return merge(&sides[0], &spl[0]);
}
Polygon clipUpLeft  (Polygon*p, double sideLen){
   double y = getMaxY(p)-sideLen;
   line splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*sides = split(p, splitLine);
   double x = getMinX(&sides[0])+sideLen;
   splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*spl=split(&sides[0], splitLine);
   return merge(&sides[1], &spl[1]);
}
Polygon clipUpRight (Polygon*p, double sideLen){
   double y = getMaxY(p)-sideLen;
   line splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*sides = split(p, splitLine);
   double x = getMaxX(&sides[0])-sideLen;
   splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*spl=split(&sides[0], splitLine);
   return merge(&sides[1], &spl[0]);
}
Polygon clipLeftLow (Polygon*p, double sideLen){
   double x = getMinX(p)+sideLen;
   line splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*sides = split(p, splitLine);
   double y = getMinY(&sides[0])+sideLen;
   splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*spl=split(&sides[0], splitLine);
   return merge(&sides[1], &spl[0]);
}
Polygon clipLeftUp  (Polygon*p, double sideLen){
   double x = getMinX(p)+sideLen;
   line splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*sides = split(p, splitLine);
   double y = getMaxY(&sides[0])-sideLen;
   splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*spl=split(&sides[0], splitLine);
   return merge(&sides[1], &spl[1]);
}
Polygon clipRightLow(Polygon*p, double sideLen){
   double x = getMaxX(p)-sideLen;
   line splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*sides = split(p, splitLine);
   double y = getMinY(&sides[1])+sideLen;
   splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*spl=split(&sides[1], splitLine);
   return merge(&sides[0], &spl[0]);
}
Polygon clipRightUp (Polygon*p, double sideLen){
   double x = getMaxX(p)-sideLen;
   line splitLine = newline(newpt(x, 0), newpt(x, 1));
   Polygon*sides = split(p, splitLine);
   double y = getMaxY(&sides[1])-sideLen;
   splitLine = newline(newpt(0, y), newpt(1, y));
   Polygon*spl=split(&sides[1], splitLine);
   return merge(&sides[0], &spl[1]);
}

double testOne(Polygon p){
   double dx = getMaxX(&p) - getMinX(&p);
   double dy = getMaxY(&p) - getMinY(&p);
   return fmax(dx, dy);
}
bool isPossible(Polygon p, int K, double sideLen){
   if(p.lines.sz == 0)
      return true;
   if(K == 1)
      return testOne(p) <= sideLen;
   if(isPossible(clipLowLeft (&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipLowRight(&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipUpLeft  (&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipUpRight (&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipLeftLow (&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipLeftUp  (&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipRightLow(&p, sideLen), K-1, sideLen)) return true;
   if(isPossible(clipRightUp (&p, sideLen), K-1, sideLen)) return true;
   return false;
}
int main(){
   int N = in_nextInt();
   int K = in_nextInt();
   Polygon source = newPolygon(N);
   double lo = 0.0;
   double hi = testOne(source);
   for(int iter=0; iter<200 && hi-lo > 1e-9; iter++){
      double m = (lo+hi)*0.5;
      if(isPossible(source, K, m))
         hi = m;
      else
         lo = m;
   }
   printf("%.2lf\n", hi);
   return 0;
}
