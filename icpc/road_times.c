#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<string.h>
#define EPS 1e-6
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int Tsz;
#define maxTsz 1111
int sizes[maxTsz];
int gSz;
vec GetRoute( int**C, int**D, int s, int e){
  vec ret=newVec();
  ret.ptr=pushback(ret.ptr, &ret.sz, s);
  while (s != e) {
    int next = -1;
    for (int i = 0; i < gSz; i++){
      if (C[s][i] > 0) {
        if (C[s][i] + D[i][e] == D[s][e]) {
          assert(next == -1);
          next = i;
        }
      }
    }
    assert(next != -1);
    ret.ptr=pushback(ret.ptr, &ret.sz, next);
    s = next;
  }
  return ret;
}
double *pushbackD(double *array, int *size, double value) {
    double *output = resizeArray(array, double, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct dvecS {
  double*ptr;
  int sz;
}vecd;
vecd newVecD() {
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vecd *pushback2(vecd *array, int *size, vecd value) {
    vecd *output = resizeArray(array, vecd, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vec2S {
  vecd*ptr;
  int sz;
}vec2;
vec2 newVec2() {
  vec2 rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int OneInColumn(vec2*T, int c, int sr){
  int one = -1;
  for (int r = sr; r < T->sz; r++) {
    if (one == -1 && fabs(T->ptr[r].ptr[c]-1) < EPS) {
      one = r;
    }
    else if (fabs(T->ptr[r].ptr[c]) > EPS) {
      return -1;
    }
  }
  return one;
}
void Pivot(vec2*T, int r, int c){
  double fact = T->ptr[r].ptr[c];
  for (int c2 = 0; c2 < T->ptr[r].sz; c2++)
    T->ptr[r].ptr[c2] /= fact;
  for (int r2 = 0; r2 < T->sz; r2++){
    if (r2 != r){
      double fact = T->ptr[r2].ptr[c];
      if (fabs(fact) < EPS)
        continue;
      for (int c2 = 0; c2 < T->ptr[r2].sz; c2++)
        T->ptr[r2].ptr[c2] -= T->ptr[r].ptr[c2] * fact;
    }
  }
}
double SimplexMethod(vec2*T){
  int rtoc[T->sz];for(int i=0;i<T->sz;i++)rtoc[i]=-1;
  for (int c = 1; c+1 < T->ptr[0].sz; c++) {
    int one = OneInColumn(T, c, 1);
    if (one == -1 || rtoc[one] != -1)
      continue;
    rtoc[one] = c;
    Pivot(T, one, c);
  }
  for (;;) {
    int c;
    for (c = 1; c+1 < T->ptr[0].sz; c++)
      if (T->ptr[0].ptr[c] > EPS)
        break;
    if (c+1 >= T->ptr[0].sz)
      break;
    int bestr = -1, bestc = -1;
    double bestratio = 1e200;
    for (int r = 1; r < T->sz; r++){
      if (T->ptr[r].ptr[c] > EPS) {
        double ratio = T->ptr[r].ptr[T->ptr[r].sz-1] / T->ptr[r].ptr[c];
        if (ratio < bestratio-EPS || ratio < bestratio+EPS && rtoc[r] < bestc) {
          bestratio = ratio;
          bestr = r;
          bestc = rtoc[r];
        }
      }
    }
    if (bestr == -1)
      return -1e200;
    Pivot(T, bestr, c);
    rtoc[bestr] = c;
  }
  return T->ptr[0].ptr[T->ptr[0].sz-1];
}
double LinearProgramming(vec2 A, vecd b, vecd c){
  vec2 T=newVec2(); T.ptr=pushback2(T.ptr, &T.sz, newVecD());
  T.ptr[0].ptr = pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,1.0);
  for (int i = 0; i < c.sz; i++)
    T.ptr[0].ptr = pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,0.0);
  for (int i = 0; i < A.sz; i++)
    T.ptr[0].ptr=pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,-1.0);
  T.ptr[0].ptr=pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,0.0);
  for (int i = 0; i < A.sz; i++){
    T.ptr=pushback2(T.ptr, &T.sz, newVecD()); for(int i=0;i<T.ptr[0].sz;i++) T.ptr[T.sz-1].ptr=pushbackD(T.ptr[T.sz-1].ptr, &T.ptr[T.sz-1].sz, 0.0);
    for (int j = 0; j < c.sz; j++)
      T.ptr[i+1].ptr[j+1] = A.ptr[i].ptr[j];
    T.ptr[i+1].ptr[c.sz+1+i] = 1.0;
    T.ptr[i+1].ptr[T.ptr[i+1].sz-1] = b.ptr[i];
  }
  if (SimplexMethod(&T) > EPS)
    return 1e200;
  for (int i = 0; i < A.sz; i++) {
    int one = OneInColumn(&T, c.sz+1+i, 0);
    if (one >= 0) {
      for (int j = 0; j < c.sz; j++){
        if (fabs(T.ptr[one].ptr[j+1]) > EPS) {
          Pivot(&T, one, j+1);
          break;
        }
      }
    }
  }
  T.ptr[0].sz=0;
  T.ptr[0].ptr=pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,1.0);
  for (int i = 0; i < c.sz; i++)
    T.ptr[0].ptr=pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,-c.ptr[i]);
  T.ptr[0].ptr=pushbackD(T.ptr[0].ptr, &T.ptr[0].sz ,0.0);
  for (int i = 1; i < T.sz; i++){
    int newsz = c.sz+2;
    T.ptr[i].ptr[newsz-1] = T.ptr[i].ptr[T.ptr[i].sz-1];
    T.ptr[i].sz=newsz;
  }
  double rv = SimplexMethod(&T);
  return rv;
}
int main(){
  int NC, NE = 0, NR, NQ;
  scanf("%d", &NC); gSz=NC;
  int**C=malloc(NC*sizeof(int*));for(int i=0;i<NC;i++)C[i]=malloc(NC*sizeof(int));
  int**D=malloc(NC*sizeof(int*));for(int i=0;i<NC;i++)D[i]=malloc(NC*sizeof(int));
  int**E=malloc(NC*sizeof(int*));for(int i=0;i<NC;i++)E[i]=malloc(NC*sizeof(int));
  for(int i=0;i<NC;i++) for(int j=0;j<NC;j++) C[i][j]=-1;
  for(int i=0;i<NC;i++) for(int j=0;j<NC;j++) D[i][j]=-1;
  for(int i=0;i<NC;i++) for(int j=0;j<NC;j++) E[i][j]=-1;
  int*EC=NULL;int ECsz=0;
  for (int x = 0; x < NC; x++){
    for (int y = 0; y < NC; y++) {
      scanf("%d", &C[x][y]);
      if (C[x][y] > 0) {
        E[x][y] = NE++;
        EC=pushback(EC, &ECsz, C[x][y]);
      }
    }
  }
  for(int i=0;i<NC;i++) for(int j=0;j<NC;j++) D[i][j]=C[i][j];
  for (int k = 0; k < NC; k++){
    for (int i = 0; i < NC; i++){
      for (int j = 0; j < NC; j++) {
        if (D[i][k] != -1 && D[k][j] != -1) {
          if (D[i][j] == -1 || D[i][k] + D[k][j] < D[i][j]) {
            D[i][j] = D[i][k] + D[k][j];
          }
        }
      }
    }
  }
  scanf("%d", &NR);
  int nenr=NE+NR;
  vec2 a=newVec2();
  for(int i=0;i<nenr;i++){
    a.ptr=pushback2(a.ptr,&a.sz,newVecD());
    for(int j=0;j<2*NE;j++)
      a.ptr[i].ptr=pushbackD(a.ptr[i].ptr, &a.ptr[i].sz, 0.0);
  }
  vecd b = newVecD();
  for( int i=0;i<nenr;i++)
    b.ptr=pushbackD(b.ptr, &b.sz, 0.0);
  for (int i = 0; i < NE; i++) {
    a.ptr[i].ptr[i   ] = 1.0;
    a.ptr[i].ptr[i+NE] = 1.0;
    b.ptr[i] = EC[i];
  }
  for (int i = 0; i < NR; i++) {
    int s, e, t;
    scanf("%d %d %d", &s, &e, &t);
    assert(D[s][e] != -1);
    vec route = GetRoute(C, D, s, e);
    for (int j = 0; j+1 < route.sz; j++) {
      int e = E[route.ptr[j]][route.ptr[j+1]];
      a.ptr[NE+i].ptr[e] = 1.0;
    }
    b.ptr[NE+i] = t - D[s][e];
  }
  scanf("%d", &NQ);
  for (int i = 0; i < NQ; i++) {
    int s, e;
    scanf("%d %d", &s, &e);
    printf("%d %d ", s, e);
    vec route = GetRoute(C, D, s, e);
    vecd c = newVecD();
    for( int i=0;i<2*NE;i++)
      c.ptr=pushbackD(c.ptr, &c.sz, 0.0);
    for (int j = 0; j+1 < route.sz; j++) {
      int e = E[route.ptr[j]][route.ptr[j+1]];
      c.ptr[e] = 1.0;
    }
    printf("%.10lf ", D[s][e] + LinearProgramming(a, b, c));
    for (int j = 0; j+1 < route.sz; j++) {
      int e = E[route.ptr[j]][route.ptr[j+1]];
      c.ptr[e] = -1.0;
    }
    int dse=D[s][e];
    double lp = LinearProgramming(a, b, c);
    double rv = dse - lp;
    printf("%.10lf\n", rv);
  }
}


















































