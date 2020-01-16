#pragma GCC optimize "-O3"
#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define newpt __builtin_complex
typedef long double ld;
typedef complex long double P;

ld norm(P p){
  ld cr = creal(p);
  ld ci = cimag(p);
  return cr*cr + ci*ci;
}


int n;
P loc[1234],v[1234];
ld ans,x,y,d,s,r;

ld dot(P a, P b){
  return creal(conj(a)*b);
}
ld moo(P p, P v){
  if(cabs(p)<r+1E-9)
    return 0;
  if(cabs(v)<1E-9)
    return(1.L/0.L);
  ld t = dot(p * newpt((ld)(-1), (ld)0), v) / norm(v);
  if(t<-1E-9)
    return((ld)(1)/(ld)(0));
  P p1 = p+v * newpt(t, 0.L);
  if(cabs(p1) > r)
    return((ld)(1)/(ld)(0));
  else
    return t-sqrt(r*r-norm(p1))/cabs(v);
}
int main(){
  int ct;
  scanf("%d", &ct);
  while(ct--){
    scanf("%d %Lf", &n, &r);
    for(int i=0; i<n; i++){
      scanf("%Lf %Lf %Lf %Lf", &x, &y, &d, &s);
      loc[i] = newpt(x, y);
      v[i] = newpt(s,0.L)*cexp(newpt(0.L,((ld)(90)-d)/(ld)(180)*M_PI));
    }
    ans = ((ld)(1)/(ld)(0));
    for(int i=0; i<n; i++)
      for(int j=0; j<i; j++) {
        ld mmm = moo(loc[i]-loc[j],v[i]-v[j]);
        if(mmm<ans)
          ans = mmm;
      }
    if(ans==((ld)(1)/(ld)(0)))
      puts("No collision.");
    else
      printf("%0.0Lf\n",ans);
  }
  return 0;
}
