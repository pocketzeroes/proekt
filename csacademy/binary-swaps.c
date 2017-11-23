#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = (int)2e6 + 100};
int a  [N];
int ans[N];
int n, k;

int main(){
    int L, R;
    int lst = -1;
    scanf("%d %d", &n, &k);
    for (int it = 0; it < n; it++){
        int z;
        scanf("%d", &z);
        if (z == 0)
            continue;
        if (lst == -1) {
            if (it >= k) {
                L = R = (int)1e6 + 3;
                a[L] = k;
                ans[it - k] = 1;
            }
            else {
                R = (int)1e6 + 3;
                L = R - (k - it);
                a[R] = it;
                ans[0] = 1;
            }
            lst = it;
            continue;
        }
        int len = it - lst - 1;
        if (len == 0) {
            R++;
            a[R] = 0;
            if (a[L] == 0)
                L++;
            else
                a[L]--;
            ans[it - k + R - L] = 1;
            lst = it;
            continue;
        }
        if (len > R - L) {
            L = R;
            a[L] = k;
            ans[it - k] = 1;
            lst = it;
            continue;
        }
        a[R]++;
        while(len > 1) {
            len--;
            R--;
            a[R] += a[R + 1] + 1;
        }
        if (a[L] == 0)
            L++;
        else
            a[L]--;
        ans[it - k + R - L] = 1;
        lst = it;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
