#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
    int n;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    qsort(v, n, sizeof(int), cmp);
    int ans = 0;
    for (int i = 1; i < n; i += 2) {
        ans += (v[i] - v[i - 1]);
    }
    printf("%d\n", ans);
    return 0;
}
