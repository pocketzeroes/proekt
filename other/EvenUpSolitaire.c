#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int m   = 0;
    int tot = 0;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        if ((v & 1) == m)
            cur += 1;
        else {
            if (cur & 1) {
                tot += 1;
                cur = 1;
            }
            else if (tot){
                tot -= 1;
                cur = 2;
            }
            else
                cur = 1;
            m = v & 1;
        }
    }
    if (cur & 1)
        tot += 1;
    printf("%d\n", tot);
    return 0;
}
