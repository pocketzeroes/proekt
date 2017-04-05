#include <stdio.h>


int main() {
    int n;
    scanf("%d", &n);
    long long cnt = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp > 0)
            cnt++;
        else {
            ans += cnt*(cnt+1)/2;
            cnt = 0;
        }
    }
    ans += cnt*(cnt+1)/2;
    printf("%lld", ans);
}
