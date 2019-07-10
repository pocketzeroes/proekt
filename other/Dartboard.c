#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
ld sigma;
ld sigma2q;
ld input[6];

ld Phi(ld a, ld b){
  return expl(-(a*a)/sigma2q)-expl(-(b*b)/sigma2q);
}
int main(){
  for(int _n=(6),t=0; t<_n; ++t) 
    scanf("%Lf",&input[t]);
  scanf("%Lf",&sigma);
  sigma2q=sigma*sigma*(ld)2.0;
  ld ret=0.0;
  ret+=(ld)50.0*Phi(0.0,input[0]);
  ret+=(ld)25.0*Phi(input[0],input[1]);
  ret+=(ld)10.5*Phi(input[1],input[2]);
  ret+=(ld)31.5*Phi(input[2],input[3]);
  ret+=(ld)10.5*Phi(input[3],input[4]);
  ret+=(ld)21.0*Phi(input[4],input[5]);
  printf("%.10Lf\n",ret);
  return 0;
}
