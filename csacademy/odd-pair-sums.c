#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

int main() {
    int N, val;
    scanf("%d %d", &N, &val);
    int ans = 0;
    for (int i = 1; i < N; ++i) {
        int newVal;
        scanf("%d", &newVal);
        if ((newVal % 2) == (val % 2)) {
            ++ans;
        }
        val = newVal;
    }
    printf("%d\n", ans);
    return 0;
}

