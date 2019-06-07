#include<stdio.h>
#include<stdlib.h>
#include<math.h>

enum{ SIZE = 20};

static double arm[SIZE];
static double min[SIZE];
static double max[SIZE];
static double x  [SIZE];
static double y  [SIZE];
static int    size;

static double minimum(double u, double v){
  if (u < v)
    return u;
  return v;
}
static double maximum(double u, double v){
  if (u > v)
    return u;
  return v;
}
static double square(double n){
  return n * n;
}
static int test2(double x, double y, double arm, double max, double u, double v, double *nu, double *nv){
  if ((u != u) || (v != v))
    return 0;
  if (fabs(square(u - x) + square(v - y) - square(arm)) > 1e-6)
    return 0;
  if (fabs(square(u) + square(v) - square(max)) > 1e-6)
    return 0;
  *nu = u;
  *nv = v;
  return 1;
}
static int test(double x, double y, double arm, double max, double *u, double *v){
  double z;
  double u1, u2;
  double v1, v2;
  double distance;
  double sum;
  sum = square(x) + square(y);
  z = (sum + square(max) - square(arm)) / 2.0;
  distance = square(max) * sum - square(z);
  if (distance < 0.0)
    distance = 0.0;
  if ((fabs(sum) < 1e-6) && (fabs(arm - max) < 1e-6)) {
    *u = arm;
    *v = 0.0;
    return 1;
  }
  v1 = (-x * sqrt(distance) + y * z) / sum;
  u1 = +sqrt(square(max) - square(v1));
  u2 = -sqrt(square(max) - square(v1));
  if ((test2(x, y, arm, max, u1, v1, u, v) != 0)||
      (test2(x, y, arm, max, u2, v1, u, v) != 0))
    return 1;
  v2 = (+x * sqrt(distance) + y * z) / sum;
  u1 = +sqrt(square(max) - square(v2));
  u2 = -sqrt(square(max) - square(v2));
  if ((test2(x, y, arm, max, u1, v2, u, v) != 0)||
      (test2(x, y, arm, max, u2, v2, u, v) != 0))
    return 1;
  return 0;
}
int main(){
  int n;
  double distance;
  double bound_min;
  double bound_max;
  scanf("%d", &size);
  for (n = 0; n < size; n++) {
    scanf("%lf", &arm[n]);
    if (n > 0) {
      if ((min[n - 1] - arm[n] < 0.0) && (max[n - 1] - arm[n] > 0.0))
        min[n] = 0.0;
      else
        min[n] = minimum(fabs(min[n - 1] - arm[n]), fabs(max[n - 1] - arm[n]));
      max[n] = max[n - 1] + arm[n];
    }
    else {
      min[n] = arm[n];
      max[n] = arm[n];
    }
  }
  scanf("%lf %lf", &x[size - 1], &y[size - 1]);
  distance = sqrt(square(x[size - 1]) + square(y[size - 1]));
  if (distance < 1e-6) {
    x[size - 1] = 0.0;
    y[size - 1] = min[size - 1];
  }
  else if (distance > max[size - 1]) {
    x[size - 1] = x[size - 1] * max[size - 1] / distance;
    y[size - 1] = y[size - 1] * max[size - 1] / distance;
  }
  else if (distance < min[size - 1]) {
    x[size - 1] = x[size - 1] * min[size - 1] / distance;
    y[size - 1] = y[size - 1] * min[size - 1] / distance;
  }
  distance = sqrt(square(x[size - 1]) + square(y[size - 1]));
  if ((distance < min[size - 1] - 1e-6) || (distance > max[size - 1] + 1e-6))
    abort();
  min[size - 1] = distance;
  max[size - 1] = distance;
  for (n = size - 2; n >= 0; n--) {
    distance = sqrt(square(x[n + 1]) + square(y[n + 1]));
    bound_min = maximum(min[n], fabs(distance - arm[n + 1]));
    bound_max = minimum(max[n], distance + arm[n + 1]);
    if (test(x[n + 1], y[n + 1], arm[n + 1], (bound_min + bound_max) / 2.0, &x[n], &y[n]) == 0)
      abort();
  }
  for (n = 0; n < size; n++)
    printf("%f %f\n", x[n], y[n]);
  return 0;
}
