#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

enum{ N   =(int) 1e6 + 1};
int cnt[N], a[N];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
        cnt[a[i]] ++;
    }
    int ans = 0;
    if(cnt[0] > 2) {
        ans += cnt[0]*(cnt[0]-1)*(cnt[0]-2)/6;
    }
    for(int i = 1; i <= 5000; i ++) {
        ans += (cnt[0]+cnt[i+i]) * cnt[i]*(cnt[i]-1)/2;
        for(int j = i+1; j + i <= 5000; j ++) {
            int s = i + j;
            ans += cnt[i]*cnt[j]*cnt[s];
        }
    }
    printf("%d\n", ans);
}
