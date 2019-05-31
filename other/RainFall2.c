#include<stdio.h>
#include<math.h>

typedef struct{
  double lo, hi;
}T;
T solve(double L, double K, double T1, double T2, double H){
  T res;
  double a, b, M, H1;
  if (H < L) 
    res.lo = res.hi = H;
  else {
    H1 = H + T2*K;
    a = H1 + K*T1;
    b = K*L*T1;
    M = (a/2) + sqrt(a*a/4 - b);
    res.hi = M;
    res.lo = H==L ? H : M;
  }
  return res;
}
int main() {
  double L, K, T1, T2, H;
  scanf("%lf%lf%lf%lf%lf", &L, &K, &T1, &T2, &H);
  T res = solve(L, K, T1, T2, H);
  printf("%1.6lf %1.6lf\n", res.lo, res.hi);
  return 0;
}
