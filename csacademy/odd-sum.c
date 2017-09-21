#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 110};
int n, a[N], res;

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for(int i = 1; i <= n; ++i)
    for(int j = i + 1; j <= n; ++j)
      if ((a[i] + a[j]) % 2)
        res++;
  printf("%d\n", res);
  return 0;
}
