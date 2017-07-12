#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

enum{ MAX_N   = (int)1e3};
enum{ MAX_VAL = (int)1e5};
enum{ INF     = (int)1e9};
int n;
int a[MAX_N];

int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int best = INF;
    int bestIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (abs(n * a[i] - sum) < best) {
            best = abs(n * a[i] - sum);
            bestIndex = i;
        }
    }
    printf("%d\n", bestIndex + 1);
}
