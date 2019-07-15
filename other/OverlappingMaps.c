#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define EPS 1e-9

int main(){
  for(int t = 1; ; t++){
    int W, H, X, Y, S, R;
    scanf("%d%d%d%d%d%d", &W, &H, &X, &Y, &S, &R);
    if(!W) 
      break;
    double theta = 3.14159265358979 * R / 180;
    double A[2][2];
    A[0][0] = cos(theta) * S / 100 - 1;
    A[0][1] = -sin(theta) * S / 100;
    A[1][0] = sin(theta) * S / 100;
    A[1][1] = cos(theta) * S / 100 - 1;
    double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    assert(det > EPS);
    printf("%.2lf %.2lf\n", (A[0][1] * Y - A[1][1] * X) / det,
                            (A[1][0] * X - A[0][0] * Y) / det);
  }
  return 0;
}
