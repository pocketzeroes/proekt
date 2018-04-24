#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#if 1
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct{
   int first;
   int second;
}pair;
pair newPair(int a, int b){
   pair rez;
   rez.first =a;
   rez.second=b;
   return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#endif

#define EPS 1e-9
#define G 9.80665

bool intersect(double vd, double vh, double dx, double dy, double x, double y1, double y2, double bh){
  if (dx < 0.0){
    dx = -dx;
    x = -x;
  }
  if (x < 0.0 || x > dx)
    return false;
  if (dx*y1 > x*dy)
    return false;
  if (dx*y2 < x*dy)
    return false;
  double d = hypot(x, x*dy/dx);
  double t = d / vd;
  double h = vh * t - G/2.0 * t*t;
  return h < bh+EPS;
}
int main(){
  double w, v;
  int dx, dy, lx, ly;
  while(scanf("%d %d %lf %lf %d %d", &dx, &dy, &w, &v, &lx, &ly)==6){
    int g   [dy+1][dx+1];
    int dist[dy+1][dx+1];
    for(int y=1; y<=dy; y++){
      for(int x=1; x<=dx; x++){
        scanf("%d", &g[y][x]);
        dist[y][x]=1000000000;
      }
    }
    int curd = 0;
    vecp q = newVecP();
    q.ptr = pushbackP(q.ptr, &q.sz, newPair(lx, ly));
    dist[ly][lx] = 0;
    while(q.sz>0){
      curd++;
      vecp q2 = newVecP();
      for(int z=0; z<q.sz; z++){pair c = q.ptr[z];
        int x, y;
        x = c.first;
        y = c.second;
        for(int x2 = 1; x2 <= dx; x2++){
          for(int y2 = 1; y2 <= dy; y2++){
            if(dist[y2][x2] > curd){
              double d = w * hypot(x2-x, y2-y);
              double h = g[y2][x2]-g[y][x];
              double a = h*h + d*d;
              double b = -2*h*h*v*v - G*d*d*h - d*d*v*v;
              double c = h*h*v*v*v*v + G*d*d*h*v*v + G*G*d*d*d*d/4;
              double disc = b*b-4*a*c;
              if(disc < -EPS)
                continue;
              double vhsqr = (-b+sqrt(disc))/2/a;
              if(vhsqr < EPS || vhsqr > v*v-EPS)
                continue;
              double vd = sqrt(v*v-vhsqr),
                     vh = sqrt(vhsqr);
              bool fail = false;
              for(int x3 = min(x, x2); !fail && x3 <= max(x, x2); x3++){
                for(int y3 = min(y, y2); !fail && y3 <= max(y, y2); y3++){
                  fail |= intersect(vd/w, vh, x2-x, y2-y, x3+0.5-x, y3-0.5-y, y3+0.5-y, g[y3][x3]-g[y][x]);
                  fail |= intersect(vd/w, vh, x2-x, y2-y, x3-0.5-x, y3-0.5-y, y3+0.5-y, g[y3][x3]-g[y][x]);
                  fail |= intersect(vd/w, vh, y2-y, x2-x, y3+0.5-y, x3-0.5-x, x3+0.5-x, g[y3][x3]-g[y][x]);
                  fail |= intersect(vd/w, vh, y2-y, x2-x, y3-0.5-y, x3-0.5-x, x3+0.5-x, g[y3][x3]-g[y][x]);
                }
              }
              if(fail)
                continue;
              q2.ptr = pushbackP(q2.ptr, &q2.sz, newPair(x2, y2));
              dist[y2][x2] = curd;
            }
          }
        }
      }
      vecp tmp;
      tmp = q;
      q   = q2;
      q2  = tmp;
    }
    for(int y=1; y<=dy; y++){
      for(int x=1; x<=dx; x++){
        if(x > 1)
          printf(" ");
        if(dist[y][x] > dx*dy)
          printf("X");
        else
          printf("%d", dist[y][x]);
      }
      puts("");
    }
  }
  return 0;
}

