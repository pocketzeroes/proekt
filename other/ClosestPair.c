#include<stdio.h>    // closestpair2
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

#define INF     1e200
#define EPSILON 1e-6
#define DMUL    1000.0
#define LMUL    1000

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pt;
typedef struct{
  pt first;
  pt second;
}pair;

int Xsize;


double ss(pt p1, pt p2){
  return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
pt*pts;

int on_x(const void*pa, const void*pb){
  int*aa=(int*)pa;
  int*bb=(int*)pb;
  int i = *aa;
  int j = *bb;
  return(pts[i].first == pts[j].first ? pts[i].second < pts[j].second : pts[i].first < pts[j].first)?-1:1;
}
int on_y(const void*pa, const void*pb){
  int*aa=(int*)pa;
  int*bb=(int*)pb;
  int i = *aa;
  int j = *bb;
  return(pts[i].second == pts[j].second ? pts[i].first < pts[j].first : pts[i].second < pts[j].second)?-1:1;
}
pair closest_point(int*X, int Xsz, int*Y, int Ysz){
  int pcount = Xsz;
  if(pcount <= 5){
    pair ret =(pair){ pts[X[0]], pts[X[1]]};
    double d = ss(ret.first, ret.second), dp;
    for (int i = 0; i < pcount; ++i){
      for (int j = i + 1; j < pcount; ++j){
        if ((dp = ss(pts[X[i]], pts[X[j]])) < d){
          d = dp;
          ret =(pair){ pts[X[i]], pts[X[j]] };
        }
      }
    }
    return ret;
  }
  int m = pcount / 2, pivot = X[m];
  if (ss(pts[X[m]], pts[X[m + 1]]) < EPSILON)
    return(pair){ pts[X[m]], pts[X[m + 1]] };
  vec Yl, Yr, Xl, Xr;
  Yl = Yr = Xl = Xr = newVec();
  for(int i = 0; i < Ysz; ++i){
    if(on_x(&Y[i], &pivot)==-1 || Y[i] == pivot)
      Yl.ptr = pushback(Yl.ptr, &Yl.sz, Y[i]);
    else
      Yr.ptr = pushback(Yr.ptr, &Yr.sz, Y[i]);
  }
  for(int i=0; i<Xsz; ++i){
    if(on_x(&X[i], &pivot)==-1 || X[i] == pivot)
      Xl.ptr = pushback(Xl.ptr, &Xl.sz, X[i]);
    else
      Xr.ptr = pushback(Xr.ptr, &Xr.sz, X[i]);
  }
  pair cl = closest_point(Xl.ptr, Xl.sz,  Yl.ptr, Yl.sz);
  pair cr = closest_point(Xr.ptr, Xr.sz,  Yr.ptr, Yr.sz);
  double delta = ss(cl.first, cl.second);
  if(ss(cr.first, cr.second) < delta){
    delta = ss(cr.first, cr.second);
    cl = cr;
  }
  vec Yp=newVec();
  ll sepx = pts[pivot].first;
  for(int i = 0; i < Ysz; ++i){
    if(abs(pts[Y[i]].first - sepx) <= delta + EPSILON)
      Yp.ptr = pushback(Yp.ptr, &Yp.sz, Y[i]);
  }
  double dp = INF;
  for (int i = 0; i < Yp.sz; ++i){
    int j = 1;
    while (i + j < Yp.sz && abs(pts[Yp.ptr[i]].second - pts[Yp.ptr[i + j]].second) <= delta + EPSILON){
      dp = ss(pts[Yp.ptr[i]], pts[Yp.ptr[i + j]]);
      if(dp < delta){
        delta = dp;
        cl =(pair){ pts[Yp.ptr[i]], pts[Yp.ptr[i + j]] };
      }
      ++j;
    }
  }
  return cl;
}
int main(){
  while(1){
    int n;
    scanf("%d", &n);
    if(n == 0)
      break;
    pts=calloc(n, sizeof(pt));
    int X[n]; clr(X);
    int Y[n]; clr(Y);
    Xsize = n;
    for(int i = 0; i < n; ++i){
      double x, y;
      scanf("%lf %lf", &x, &y);
      pts[i] =(pt){ (ll)(y * LMUL), (ll)(x * LMUL) };
      X[i] = Y[i] = i;
    }
    qsort(X, n, sizeof(int), on_x);
    qsort(Y, n, sizeof(int), on_y);
    pair cl = closest_point(X, n, Y, n);
    printf("%.2f %.2f %.2f %.2f\n", cl.first.second / DMUL, cl.first.first / DMUL, cl.second.second / DMUL, cl.second.first / DMUL);
  }
  return 0;
}
