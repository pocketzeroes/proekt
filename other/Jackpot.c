#include <stdio.h>

#define MAX_WHEELS 20
#define MAX_SPINS 1e9

int euclid(int a, int b){
  if (a)
    return euclid(b % a, a);
  else
    return b;
}
int main(){
  int i, m, n, t[MAX_WHEELS];
  scanf("%d", &n);
  while (n--){
    scanf("%d", &m);
    for (i=0; i<m; i++){
      scanf("%d", t+i);
    }
    for (i=0; i<m-1; i++){
      t[i] = t[i] / euclid(t[i],t[i+1]);
      if (MAX_SPINS / t[i] < t[i+1])
        break;
      else
        t[i+1] = t[i] * t[i+1];
    }
    if (i < m - 1)
      printf("More than a billion.\n");
    else
      printf("%d\n", t[m-1]);
  }
  return 0;
}


