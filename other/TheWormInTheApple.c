#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
enum{ MAXN = 1010};

typedef long long ll;

typedef struct{
  ll X[3];
}v3;
v3 newv3(ll x, ll y, ll z){
  v3 rez;
  rez.X[0] = x;
  rez.X[1] = y;
  rez.X[2] = z;
  return rez;
}
v3 opMul(v3 a, v3 v){
  return newv3(a.X[1]*v.X[2]-a.X[2]*v.X[1],
               a.X[2]*v.X[0]-a.X[0]*v.X[2],
               a.X[0]*v.X[1]-a.X[1]*v.X[0]);
}
v3 opSub(v3 a, v3 v){
  return newv3(a.X[0]-v.X[0], a.X[1]-v.X[1], a.X[2]-v.X[2]);
}
v3 opNeg(v3 a){
  return newv3(-a.X[0], -a.X[1], -a.X[2]);
}
ll dot(v3 a, v3 v){
  return a.X[0]*v.X[0] + a.X[1]*v.X[1] + a.X[2]*v.X[2];
}
v3 A[MAXN];

typedef struct{
  int a, b;
}twoset;
twoset E[MAXN][MAXN];

inline void insert(twoset*t, int x){
  if(t->a == -1)
    t->a=x;
  else
    t->b=x;
}
inline bool contains(twoset t, int x){
  return t.a == x || t.b == x;
}
inline void erase(twoset*t, int x){
  if(t->a == x)
    t->a=-1;
  else
    t->b=-1;
}
inline int size(twoset t){
  return (t.a != -1) + (t.b != -1);
}

typedef struct{
  v3  norm;
  ll  disc;
  int I[3];
}face;

face newFace(int i, int j, int k, int inside_i){
  insert(&E[i][j], k); 
  insert(&E[i][k], j); 
  insert(&E[j][k], i);
  face f;
  f.I[0] = i; 
  f.I[1] = j; 
  f.I[2] = k;
  f.norm = opMul(opSub(A[j], A[i]), opSub(A[k], A[i]));
  f.disc = dot(f.norm, A[i]);
  if(dot(f.norm, A[inside_i]) > f.disc){
    f.norm = opNeg(f.norm);
    f.disc = -f.disc;
  }
  return f;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
face*pushbackF(face*array, int *size, face value){
  face*output = resizeArray(array, face, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	face*ptr;
	int sz;
}vecf;
vecf newVecF(){
	vecf rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int main() {
  int N;
  for(scanf("%d", &N); N; scanf("%d", &N)){
    for(int i=0; i<N; i++){
      scanf("%lld%lld%lld", &A[i].X[0], &A[i].X[1], &A[i].X[2]);
    }
    face f;
    vecf faces = newVecF();
    memset(E, -1, sizeof(E));
    for(int i = 0; i < 4; i++)
      for(int j = i + 1; j < 4; j++)
        for(int k = j + 1; k < 4; k++) {
          faces.ptr = pushbackF(faces.ptr, &faces.sz, newFace(i, j, k, 6 - i - j - k));
        }
    for(int i = 4; i < N; i++){
      for(int j = 0; j < faces.sz; j++){
        f = faces.ptr[j];
        if(dot(f.norm, A[i]) > f.disc){
          for(int a = 0; a < 3; a++)
            for(int b = a + 1; b < 3; b++){
              int c = 3 - a - b;
              erase(&E[f.I[a]][f.I[b]], f.I[c]);
            }
          faces.ptr[j--] = faces.ptr[faces.sz-1];
          faces.sz--;
        }
      }
      int nfaces = faces.sz;
      for(int j = 0; j < nfaces; j++){
        f = faces.ptr[j];
        for(int a = 0; a < 3; a++) 
          for(int b = a + 1; b < 3; b++) {
            int c = 3 - a - b;
            if(size(E[f.I[a]][f.I[b]]) == 2)
              continue;
            faces.ptr = pushbackF(faces.ptr, &faces.sz, newFace(f.I[a], f.I[b], i, f.I[c]));
          }
      }
    }
    int Q;
    scanf("%d", &Q);
    for(int i=0; i<Q; i++){
      v3 v; 
      scanf("%lld%lld%lld", &v.X[0], &v.X[1], &v.X[2]);
      double dist = 1e300;
      for(int i = 0; i < faces.sz; i++){
        ll d = faces.ptr[i].disc - dot(faces.ptr[i].norm, v);
        dist = min(dist, 1. * d / sqrt(dot(faces.ptr[i].norm, faces.ptr[i].norm)));
      }
      printf("%.4f\n", dist);
    }
    break;
  }
  return 0;
}
