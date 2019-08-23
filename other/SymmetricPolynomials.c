#include<stdio.h>
#include<math.h>
enum{ MAXD=11};
int nm, n[2], c[2][11];

double eval(int who, double t){
  int i;
  double pow = 1.0;
  double sum = 0.0;
  for (i = 0; i <= n[who]; i++){
    sum += c[who][i] * pow;
    pow *= t;
  }
  return sum;
}
int symcheck(int a, int b, double t0){
  int i, j;
  int sym = 1;
  double cf[2][MAXD];
  for (i = 0; i <= nm; i++)
    cf[0][i] = cf[1][i] = 0.0;
  for (i = 0; i <= nm; i++) {
    double talj = 1.0;
    double namn = 1.0;
    double t0p = 1.0;
    for (j = i; j >= 0; j--) {
      cf[0][j] += talj * c[0][i] * t0p / namn;
      cf[1][j] += talj * c[1][i] * t0p / namn;
      t0p *= t0;
      talj *= (j);
      namn *= (i-j+1);
    }
  }
  for (i = 1; i <= nm && sym; i++) {
    double delta;
    if (i & 1)
      delta = -b * cf[0][i] + a * cf[1][i];     
    else 
      delta = a * cf[0][i] + b * cf[1][i];
    sym &= fabs(delta)<1e-8;
  }
  return sym;
}
int main(){
  int i, j;
  int a, b;
  for (j = 0; j < 2; j++) {
    for (i = 0; i < MAXD; i++)
      c[j][i] = 0.0; 
    scanf("%d", &n[j]);
    for (i = 0; i < n[j] + 1; i++)
      scanf("%d", &c[j][n[j]-i]);
  }
  if (!n[0] && !n[1]) {
    if (!c[0][0] && !c[1][0])
      printf("1 0 0\n");
    else  
      printf("%d %d 0\n", c[1][0], -c[0][0]);
  }
  else { 
    nm = n[0] > n[1] ? n[0] : n[1];
    a = c[0][nm];
    b = c[1][nm];
    int d,dt;
    dt = a * n[0] * c[0][nm] + b * n[1] * c[1][nm];
    d = a * c[0][nm-1] + b * c[1][nm-1];
    if (dt) {
      double t0 = -((double)d) / dt;
      double x0 = eval(0, t0);
      double y0 = eval(1, t0);
      if (nm % 2 == 0) {
        a = c[1][nm];
        b = -c[0][nm];
      }
      if (symcheck(a, b, t0))
        printf("%d %d %1.6lf\n", a, b, -x0 * a - y0 * b);
      else
        printf("0 0 0\n"); 
    }
    else 
      printf("0 0 0\n");
  }
  return 0;
}
