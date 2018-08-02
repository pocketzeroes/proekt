#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
  int n, q, x;
  scanf("%d %d %d", &n, &q, &x);
  while(q--){
    int a, b;
    scanf("%d %d", &a, &b);
    if(a == x)
        x = b;
    else if(b == x)
        x = a;
  }
  printf("%d\n", x);
  return 0;
}
