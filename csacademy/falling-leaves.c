#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ maxn = 100005};
int T, C, N;
int ans[maxn];

int main(){
    scanf("%d %d %d", &T, &C, &N);
    for(int i=0, iend=N; i<iend; i++){
        ll x, y, s;
        scanf("%lld %lld %lld", &x, &y, &s);
        ll u = y * C - x * s;
        ll d = s * C;
        if (u % d == 0 && u >= 0){
            ll now = u / d;
            if (now < maxn)
                ++ans[now];
        }
    }
    for(int i=0,iend=T;i<iend;i++)
        printf("%d\n", ans[i]);
    return 0;
}




























