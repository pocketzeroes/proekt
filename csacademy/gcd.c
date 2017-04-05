#include <stdio.h>

int gcd(int u, int v ){
  return v != 0?gcd(v, u%v):u;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", gcd(a , b));
    return 0;
}
