#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double *pushbackD(double *array, int *size, double value) {
  double *output = resizeArray(array, double, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  double*ptr;
  int sz;
}vecd;
vecd newVecD(){
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpD(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}

/////////////////////////
int C, N[51];
double P[51][51][2], totLen, watLen, way1[3], way2[3], v1[3], v2[3];

void toCart(double *P, double *cart){
  cart[0] = sin(P[0]) * cos(P[1]);
  cart[1] = sin(P[0]) * sin(P[1]);
  cart[2] = cos(P[0]);
}
double distC(double *V1, double *V2){
  return 6370*acos((V1[0]*V2[0] + V1[1]*V2[1] + V1[2]*V2[2]));
}
int main(){
  scanf("%d", &C);
  for(int i=0; i<C+1; i++){
    scanf("%d", &N[i]);
    for(int j=0; j<N[i]; j++)
      for(int k=0; k<2; k++){
        scanf("%lf", &P[i][j][k]);
        if(k == 0)
          P[i][j][k] += 90;
        P[i][j][k] = (2.*acos(0)*(P[i][j][k])/180.);
      }
  }
  bool inside = true;
  toCart(P[C][0], way2);
  for(int i=(0); i<(N[C]-1); i++){
    for(int j=(0); j<(3); j++)
      way1[j] = way2[j];
    toCart(P[C][i+1], way2);
    vecd alldists = newVecD();
    for(int j=0; j<C; j++)
      for(int k=0; k<N[j]; k++){
        toCart(P[j][k], v1);
        toCart(P[j][(k+1)%N[j]], v2);
        double alpha = 0, omega = 1, fullDst = distC(way1, way2), mid[2], v[2][3], diff[2], bestDiff = 500000, retD;
        for(int i=0; i<50; i++){
          for(int j=0; j<2; j++){
            mid[j] = alpha + (1+j)*(omega-alpha)/3.;
            for(int k=0; k<3; k++)
              v[j][k] = v1[k] + mid[j]*(v2[k] - v1[k]);
            double len = (sqrt((v[j][0]*v[j][0] + v[j][1]*v[j][1] + v[j][2]*v[j][2])));
            for(int k=0; k<3; k++)
              v[j][k] /= len;
            diff[j] = fabs(fullDst - distC(v[j], way1) - distC(v[j], way2));
          }
          if(diff[0] < diff[1])
            omega = mid[1];
          else
            alpha = mid[0];
          retD = distC(v[0], way1);
          bestDiff = fmin(bestDiff, fmin(diff[0], diff[1]));
        }
        if(bestDiff < 0.000001)
          alldists.ptr = pushbackD(alldists.ptr, &alldists.sz, retD);
      }
    qsort(alldists.ptr, alldists.sz, sizeof(double), cmpD);
    totLen += distC(way1, way2);
    double last = 0;
    for(int i=0; i<alldists.sz; inside=!inside, last=alldists.ptr[i], i++){
      if(!inside)
        watLen += alldists.ptr[i] - last;
    }
    if(!inside)
      watLen += distC(way1, way2) - last;
  }
  printf("%.10lf %.10lf\n", totLen, (100.*watLen/totLen) );
  return 0;
}
