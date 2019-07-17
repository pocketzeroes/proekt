#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int gcd(int a, int b){
  if (a == 0)
    return b;
  else
    return gcd(b%a, a);
}
int gcd_result[101][101];
int a[100000];

int main(){
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= 100; ++i) {
    for (int j = 1; j <= 100; ++j)
      gcd_result[i][j] = gcd(i, j);
  }
  while (n){
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 1; i <= 100; ++i) {
      int tmp = 0;
      bool flag = false;
      for (int j = 0; j < n; ++j){
        if (a[j] % i != 0) {
          tmp = 0;
          continue;
        }
        if (tmp == 0) {
          tmp = a[j];
        }
        else {
          tmp = gcd_result[tmp][a[j]];
        }
        if (tmp == i){
          flag = true;
          break;
        }
      }
      if (flag) {
        ++ans;
      }
    }
    printf("%d\n", ans);
    break;
    scanf("%d", &n);
  }
  return 0;
}
