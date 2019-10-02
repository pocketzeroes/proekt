#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef double dbl;
typedef long long ll;

inline ll  sq(ll  x){return x*x;}
inline dbl sqf(dbl x){return x*x;}

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
ll**newmat(int x, int y){
  ll**rv = calloc(x, sizeof(ll*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(ll));
  return rv;
}
void freemat(ll**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

dbl EPS = 1e-9;
int PENALTY = 1000000;
int N, M;
ll R;
ll*x;
ll*y;
ll*r;
ll**d;

typedef struct State{
  dbl angle;
  int inc;
}State;
State newState(dbl a, int i){
  return(State){a,i};
}
int cmpS(const void*pa, const void*pb){
  State*this =(State*)pa;
  State*other=(State*)pb;
  if(this->angle < other->angle)
    return-1;
  if(this->angle > other->angle)
    return 1;
  return 0;
}
#define pb(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
State*pushbackS(State*array, int *size, State value){
  State*output = resizeArray(array, State, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	State*ptr;
	int sz;
}vecs;
vecs newVecS(){
	vecs rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////////


dbl*getCircle(int i1, int i2, dbl rad, int type){
  dbl L = r[i1] + rad;
  dbl R = r[i2] + rad;
  dbl D = d[i1][i2];
  dbl c = (D+L*L-R*R)/2.;
  dbl b = sqrt(D*L*L-c*c);
  dbl nx = (x[i2] - x[i1]) / D, ny = (y[i2] - y[i1]) / D;
  dbl bx = -ny * b, by = nx * b;
  dbl ax = nx * c, ay = ny * c;
  dbl*rv=calloc(2, sizeof(dbl));
  if(type == 0){
    rv[0]=x[i1] + ax - bx;
    rv[1]=y[i1] + ay - by;
  }
  else{
    rv[0]=x[i1] + ax + bx;
    rv[1]=y[i1] + ay + by;
  }
  return rv;
}
int solvePoint(int f){
  vecs w = newVecS();//of State
  int cur = 1;
  for(int i = 0; i < N+M; i++){
    if(i == f)
      continue;
    ll reach = sq(2*R+r[i]);
    ll dist = d[i][f];
    if(dist > reach)
      continue;
    dbl q[2];
    for(int j=0; j<2; j++){
      dbl*c = getCircle(f, i, R, j);
      q[j] = atan2(c[1]-y[f],c[0]-x[f]);
      free(c);
    }
    int add = i < N ? -PENALTY : 1;
    if(q[1] < q[0])
      cur += add;
    pb(w, newState(q[0] - EPS, add));
    pb(w, newState(q[1] + EPS,-add));
  }
  qsort(w.ptr, w.sz, sizeof(State), cmpS);
  int res = cur;
  for(int z=0;z<w.sz;z++){State s = w.ptr[z];
    cur += s.inc;
    res = fmax(res, cur);
  }
  return res;
}
int checkCircle(dbl*c, dbl rad){
  for (int k = 0; k < N; k++) {
    dbl d = sqf(c[0] - x[k])+
            sqf(c[1] - y[k]);
    if(d < sqf(r[k]+rad-EPS))
      return 0;
  }
  int count = 0;
  for (int k = N; k < N+M; k++) {
    dbl d = sqf(c[0] - x[k])+
            sqf(c[1] - y[k]);
    if(d <= sqf(rad + EPS))
      count++;
  }
  free(c);
  return count;
}
int solveVillages(int v1, int v2){
  int res = 0;
  for (int i = N; i < N+M; i++) {
    ll dist = d[v1][i];
    ll reach = sq(r[v1] + r[i] + 2 * R);
    if (dist > reach)
      continue;
    for (int j = 0; j < 2; j++) {
      dbl lo = (sqrt(d[v1][i]) - r[v1] - r[i]) / 2.,
          hi = R;
      for (int iter = 0; iter < 200; iter++){
        dbl mid = (lo + hi) / 2.;
        dbl*c = getCircle(v1,i,mid,j);
        dbl d = sqf(c[0] - x[v2])+
                sqf(c[1] - y[v2]);
        free(c);
        if(d < sqf(r[v2] + mid + EPS))
          hi = mid;
        else
          lo = mid;
      }
      res = fmax(res, checkCircle(getCircle(v1,i,lo,j), lo));
    }
  }
  return res;
}


int main(){
  N = in_nextInt();
  M = in_nextInt();
  R = in_nextInt();
  x = calloc(N+M, sizeof(ll));
  y = calloc(N+M, sizeof(ll));
  r = calloc(N+M, sizeof(ll));
  for(int i = 0; i < N; i++){
    x[i] = in_nextInt();
    y[i] = in_nextInt();
    r[i] = in_nextInt();
  }
  for(int i = N; i < N+M; i++){
    x[i] = in_nextInt();
    y[i] = in_nextInt();
    r[i] = 0;
  }
  d = newmat(N+M, N+M);//of ll
  for(int i = 0; i < N+M; i++)
    for(int j = 0; j < N+M; j++)
      d[i][j] = sq(x[i]-x[j]) + sq(y[i]-y[j]);
  int best = 1;
  for(int i = N; i < N+M; i++)
    best = fmax(best, solvePoint(i));
  for(int i = 0; i < N; i++)
    for(int j = i+1; j < N; j++)
      best = fmax(best, solveVillages(i, j));
  freemat(d, N+M);
  free(x);
  free(y);
  free(r);
  printf("%d\n", best);
  return 0;
}
