#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
  

enum{ N_MAX =(int) 1e5};
int N, M, F1, F2;
int x[N_MAX + 5], y[N_MAX + 5];

int*G    [N_MAX + 5];
int sizes[N_MAX + 5];
int64_t fx[N_MAX + 5], fy[N_MAX + 5];

void Solve(int a[], int64_t*f){
   int64_t s = 0;
   for (int i = 1; i <= N; ++i)
      s += a[i];
   for (int i = 1; i <= N; ++i) {
      f[i] = ((int64_t)N * a[i] - s) * F2;
      for(int z=0;z<sizes[i];z++){
         int j = G[i][z];
         f[i] += (int64_t)(F1 - F2) * (a[i] - a[j]);
      }
   }
}
int main() {
   scanf("%d %d %d %d", &N, &M, &F1, &F2);
   while (M--) {
      int xx, yy;
      scanf("%d %d", &xx, &yy);
      G[xx]=pushback(G[xx], sizes+xx, yy);
      G[yy]=pushback(G[yy], sizes+yy, xx);
   }
   for (int i = 1; i <= N; ++i)
      scanf("%d %d", &x[i] , &y[i]);
   Solve(x, fx);
   Solve(y, fy);
   for (int i = 1; i <= N; ++i)
      printf("%lld %lld\n", fx[i], fy[i]);
   return 0;
}




















