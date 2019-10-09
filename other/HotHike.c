#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int n;
  scanf("%d", &n);
  int best_t = 47,
      best_d = -1;
  int t[n];
  for(int i=0; i<n; ++i)
    scanf("%d", &t[i]);
  for(int i=0; i<n-2; ++i){
    int cur = fmax(t[i], t[i + 2]);
    if(cur < best_t){
      best_t = cur;
      best_d = i + 1;
    }
  }
  printf("%d %d\n", best_d, best_t);
  return 0;
}
