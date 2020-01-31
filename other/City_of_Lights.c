#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int a[1000010];

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        a[i] = 1;
    int ans = 0, cur = 0;
    while (k--){
        int m, cnt = cur;
        scanf("%d", &m);
        for (int i = 1; i * m <= n; i++){
            if (!a[i * m])
                cnt--;
            else
                cnt++;
            a[i * m] ^= 1;
        }
        ans = fmax(ans, cnt);
        cur = cnt;
    }
    printf("%d\n", ans);
    return 0;
}
