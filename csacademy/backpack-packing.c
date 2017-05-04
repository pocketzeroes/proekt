#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    int ans = 0;
    for (int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        if (a < b)
            SWAP(a, b);
        if (x <= a)
            a -= x;
        else
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
