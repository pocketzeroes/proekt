#include<math.h>
#include<stdio.h>
#include<string.h>

#define LOG2 19
#define SIZE (1 << LOG2)

typedef double complex_t[2];

static complex_t distance[SIZE];
static int      reachable[SIZE];

static void swap(complex_t x, complex_t y){
  complex_t z;
  z[0] = x[0];
  z[1] = x[1];
  x[0] = y[0];
  x[1] = y[1];
  y[0] = z[0];
  y[1] = z[1];
}
static void multiply(complex_t z, complex_t x, complex_t y){
  complex_t dst;
  dst[0] = x[0] * y[0] - x[1] * y[1];
  dst[1] = x[1] * y[0] + x[0] * y[1];
  z[0] = dst[0];
  z[1] = dst[1];
}
static void set(complex_t x, double r, double i){
  x[0] = r;
  x[1] = i;
}
static void fft(complex_t *xy, int m, int direction){
  int n, i, i1, j, k, i2, l, l1, l2;
  complex_t c, t, u;
  n = 1;
  for (i = 0; i < m; i++)
    n <<= 1;
  i2 = n >> 1;
  j = 0;
  for (i = 0; i < n - 1; i++) {
    if (i < j)
      swap(xy[i], xy[j]);
    k = i2;
    while (k <= j) {
      j -= k;
      k >>= 1;
    }
    j += k;
  }
  set(c, -1.0, 0.0);
  l2 = 1;
  for (l = 0; l < m; l++) {
    l1 = l2;
    l2 <<= 1;
    set(u, 1.0, 0.0);
    for (j = 0; j < l1; j++) {
      for (i = j; i < n; i += l2) {
        i1 = i + l1;
        multiply(t, u, xy[i1]);
        xy[i1][0] = xy[i][0] - t[0];
        xy[i1][1] = xy[i][1] - t[1];
        xy[i][0] += t[0];
        xy[i][1] += t[1];
      }
      multiply(u, u, c);
    }
    c[1] = sqrt((1.0 - c[0]) / 2.0);
    if (direction > 0)
      c[1] = -c[1];
    c[0] = sqrt((1.0 + c[0]) / 2.0);
  }
  if (direction > 0) {
    for (i = 0; i < n; i++) {
      xy[i][0] /= n;
      xy[i][1] /= n;
    }
  }
}
int main(){
  int v, size;
  int possible;
  memset(distance , 0, sizeof(distance) );
  memset(reachable, 0, sizeof(reachable));
  for (scanf("%d", &size); size > 0; size--) {
    scanf("%d", &v);
    distance[v][0] = 1.0;
    reachable[v] = 1;
  }
  fft(distance, LOG2, -1);
  for (size = 0; size < SIZE; size++)
    multiply(distance[size], distance[size], distance[size]);
  fft(distance, LOG2, +1);
  possible = 0;
  for (scanf("%d", &size); size > 0; size--) {
    scanf("%d", &v);
    if ((distance[v][0] > 0.5) || (reachable[v] != 0))
      possible++;
  }
  printf("%d\n", possible);
  return 0;
}
