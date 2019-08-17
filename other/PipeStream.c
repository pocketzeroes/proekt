#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int T;
  for(scanf("%d", &T); T--;){
    int L, V1, V2, Tol, S;
    scanf("%d%d%d%d%d", &L, &V1, &V2, &Tol, &S);
    int leaves = (V2-V1+Tol-1)/Tol, minv = V2-leaves*Tol, nodes = 1, depth = 0;
    while (nodes > 0 && leaves > nodes){
      depth++;
      int maxv = L / (S*depth);
      int leaves2 = fmin(leaves, (maxv-minv+Tol)/Tol);
      nodes -= leaves - leaves2;
      nodes *= 2;
      leaves = leaves2;
    }
    if (nodes <= 0)
      puts("impossible");
    else
      printf("%d\n", depth);
  }
  return 0;
}
