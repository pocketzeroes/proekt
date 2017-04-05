#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int __gcd(int u, int v ){
  return v != 0?__gcd(v, u%v):u;
}



int n, m;
int a[120000];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    int ans = a[0];
    for (int i = 1; i < n; ++i)
        ans = __gcd(ans, a[i]);
    for (int i = 0; i < m; ++i) {
        int x;
        int y;
        scanf("%d%d", &x, &y);
        --x;
        a[x] /= y;
        ans = __gcd(ans, a[x]);
        printf("%d\n", ans);
    }
    return 0;
}
