#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

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
typedef struct{
  pair first;
  pair second;
}quad;
quad newQuad(pair a, pair b){
  quad rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
quad*pushbackQ(quad*array, int *size, quad value){
  quad*output = resizeArray(array, quad, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	quad*ptr;
	int sz;
}vecq;
vecq newVecQ(){
	vecq rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
double *pushbackD(double *array, int *size, double value) {
    double *output = resizeArray(array, double, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
  double*ptr;
  int sz;
}vecd;
vecd newVecD() {
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
///////////////////////////////
enum{ N = 2100 };
#define EPS 1E-8

pair wektor[N];
vecq v     [N]; // of quad
vecd dist  [N]; //of double

inline int dot(pair p1, pair p2){
  return p1.first * p2.second - p1.second * p2.first;
}
inline int scalar(pair p1, pair p2){
  return p1.first * p2.first + p1.second * p2.second;
}
void give_ac(quad p, double*a, double*c){
  double x0 = p.first.first;
  double y0 = p.first.second;
  double x1 = p.second.first;
  double y1 = p.second.second;
 *a = (y1-y0) / (x1-x0);
 *c = y0 -  *a  * x0;
}
int main(){
  int n;
  scanf("%d",&n);
  int g = 0;
  for (int foo=0; foo<(n); ++foo){
    int x0, y0, x1, y1;
    scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
    int a = x1-x0;
    int b = y1-y0;
    int which = -1;
    for (int i=0; i<(g); ++i){
      if (dot(wektor[i],newPair(a,b)) == 0){
        which = i;
        break;
      }
    }
    if (which == -1) {
      wektor[g] = newPair(a,b);
      which = g++;
    }
    v[which].ptr = pushbackQ(v[which].ptr, &v[which].sz, newQuad(newPair(x0,y0),newPair(x1,y1)));
  }
  for (int i=0; i<(g); ++i){
//  dist[i].reserve((int)v[i].sz * (int)v[i].sz / 2);
    for (int a=0; a<((int)v[i].sz); ++a){
      for (int b=0; b<(a); ++b){
        if (wektor[i].first == 0){
          dist[i].ptr = pushbackD(dist[i].ptr, &dist[i].sz, abs(v[i].ptr[a].first.first - v[i].ptr[b].first.first));
        }
        else{
          double a1, b1 = 1.0, c1;
          double a2, b2 = 1.0, c2;
          give_ac(v[i].ptr[a], &a1, &c1);
          give_ac(v[i].ptr[b], &a2, &c2);
          double d = fabs(c1-c2) / sqrt(a1 * a1 + b1 * b1);
          dist[i].ptr = pushbackD(dist[i].ptr, &dist[i].sz, d);
        }
      }
    }
    qsort(dist[i].ptr, dist[i].sz, sizeof(double), cmpDbl);
  }
  ll res = 0;
  for (int i=0; i<(g); ++i){
    for (int j=0; j<(i); ++j){
      if (scalar(wektor[i],wektor[j]) == 0){
        int a = 0, b = 0;
        while (a < (int)dist[i].sz && b < (int)dist[j].sz){
          if (dist[i].ptr[a] + EPS < dist[j].ptr[b]){
            a++;
            continue;
          }
          if (dist[j].ptr[b] + EPS < dist[i].ptr[a]) {
            b++;
            continue;
          }
          double x = dist[i].ptr[a];
          int c1 = 0, c2 = 0;
          while (a < (int)dist[i].sz && fabs(dist[i].ptr[a]-x) < EPS)
            a++, c1++;
          while (b < (int)dist[j].sz && fabs(dist[j].ptr[b]-x) < EPS)
            b++, c2++;
          res += (ll)c1 * c2;
        }
      }
    }
  }
  printf("%lld\n", res);
  return 0;
}
