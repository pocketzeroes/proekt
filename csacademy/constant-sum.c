#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{ MAX_N = (int)1e5};
enum{ MAX_Q = (int)1e5};
int a[MAX_N + 1];
int add[MAX_N + 1];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int sum = 0;
    for (int t = 0; t < q; ++t) {
        int op, i, val;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d %d", &i, &val);
            add[i] += val;
            sum    += val;
        } 
        else {
            scanf("%d", &i);
            printf("%.10f\n", a[i] + add[i] - ((double)sum - add[i]) / (n - 1) );
        }
    }
    return 0;
}
