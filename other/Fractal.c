#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>

#define newpt __builtin_complex
typedef complex double pt;
const double eps = 1e-10;

int main (){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    int N,D;
    double f;
    scanf("%d", &N);
    pt x[N],dx[N-1];
    for(int i=0; i<N; i++){
      double real, imag;
      scanf("%lf%lf", &real, &imag);
      x[i] = newpt(real, imag);
      if(i)
        dx[i-1] = x[i] - x[i-1];
    }
    scanf("%d %lf", &D, &f);
    double L=0.;
    for(int i=0; i<N-1; i++)
      L += cabs(dx[i]);
    double s = L / cabs(x[N-1]-x[0]);
    double dist = f * L;
    pt X = x[0], b = newpt(1., 0.);
    for(int d=0; d<D; d++){
      int i=0;
      while(i<N-1 && cabs(b*dx[i])<dist*(1-eps)){
        dist -= cabs(b*dx[i]);
        X += b*dx[i];
        i++;
      }
      if(d==D-1)
        X += dist * b*dx[i]/cabs(b*dx[i]);
      b *= dx[i]/(x[N-1]-x[0]);
      dist *= s;
    }
    printf("%.10lf %.10lf\n", creal(X), cimag(X));
  }
  return 0;
}
