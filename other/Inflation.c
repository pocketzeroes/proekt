#include<stdio.h>
#include<stdlib.h>

int main(){
  int n;
  scanf("%d", &n);
  int *v = (int*) malloc(sizeof(int) * n);
  int *c = (int*) malloc(sizeof(int) * (n+1));
  for (int i = n; i --> 0;) {
    int x;
    scanf("%d", &x);
    c[x]++;
  }
  for (int i = 0, j = 0; i <= n; i++){
    while (c[i]--)
      v[j++] = i;
  }
  float res = 1.0;
  for (int i = 0; i < n; i++) {
    float candidate = v[i] / (float) (i+1);
    if (candidate < res)
      res = candidate;
    if (v[i] > i+1) {
      puts("impossible");
      goto finish;
    }
  }
  printf("%.8f\n", res);
 finish:
  free(c);
  free(v);
  return 0;
}
