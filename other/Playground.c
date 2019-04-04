#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpD(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
int main(){
  enum{ MAX_K = 20};
  double val[MAX_K];
  while (true){
    int K;
    scanf("%d", &K);
    if (K == 0)
      return 0;
    for (int i = 0; i < K; i++)
      scanf("%lf", &val[i]);
    qsort(val, K, sizeof(double), cmpD);
    double sum = 0.0;
    double max = 0.0;
    bool good = false;
    for (int i = 0; i < K; i++){
      max = val[i] > max ? val[i] : max;
      sum += val[i];
      if (sum - max >= max){
        good = true;
        break;
      }
    }
    if (good)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
