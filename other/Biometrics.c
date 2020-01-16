#include<stdio.h>
#include<math.h>

#define sq(x) ((x)*(x))

int x[10],y[10],X[10],Y[10];
int i,j,k,f,a,A,d,D,s,S;
int main(){
  while (1 == scanf("%d",&f) && f) {
    for (i=0;i<f;i++)
      scanf("%d%d",&x[i],&y[i]);
    for (i=0;i<f;i++)
      scanf("%d%d",&X[i],&Y[i]);
    a = sq(x[0]-x[1]) + sq(y[0]-y[1]);
    A = sq(X[0]-X[1]) + sq(Y[0]-Y[1]);
    for (i=0;i<f;i++)
      for (j=0;j<f;j++) {
        d = sq(x[i]-x[j]) + sq(y[i]-y[j]);
        D = sq(X[i]-X[j]) + sq(Y[i]-Y[j]);
        if ((long long)a*D != (long long)A*d)
          goto foo;
      }
    for (i=2;i<f;i++){
      s = (x[1]-x[0])*(y[i]-y[0]) - (y[1]-y[0])*(x[i]-x[0]);
      S = (X[1]-X[0])*(Y[i]-Y[0]) - (Y[1]-Y[0])*(X[i]-X[0]);
      if (s < 0 && S > 0 || s > 0 && S < 0)
        goto foo;
    }
    printf("similar\n");
    continue;
   foo: printf("dissimilar\n");
  }
  if (f)
    printf("missing end delimiter\n");
  return 0;
}
