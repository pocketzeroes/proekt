#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ maxn=500000+5 };
enum{ MOD=1000000009};
int n;
int a[maxn], b[maxn], pre[maxn];
ll p2[maxn];

ll work(int*a, bool op){
    ll ret=0;
    pre[0]=0;
    for(int i=1; i<=n; i++){
        pre[i]=pre[i-1]+a[i];
        int j=n+2-i;
        if (j>i){
            ret+=((p2[pre[i-1]]*(p2[a[i]]-1))%MOD*(i-1))%MOD;
            ret%=MOD;
        }
        else if (j == i){
            ret+=(p2[pre[i-1]])*(p2[a[i]]-1)%MOD*(i-1)%MOD;
            ret%=MOD;
            if (op){
                ll tmp=(p2[a[1]])*(p2[a[i]]-1)%MOD*(i-1)%MOD;
                ret = (ret+MOD-tmp)%MOD;
            }
        }
        else {
            ll tmp=(p2[pre[j]-pre[1]]-1)*(p2[a[1]])%MOD*(p2[pre[i-1]-pre[j]])%MOD*(p2[a[i]]-1)%MOD;
            tmp%=MOD;
            tmp*=(i-1);
            tmp%=MOD;
            ret=(ret+tmp)%MOD;
            if (op){
                tmp = (p2[a[i]]-1)*(p2[a[j]]-1)%MOD*(p2[pre[i-1]-pre[j]])%MOD*(i-1)%MOD*(p2[a[1]])%MOD;
                ret = (ret+MOD-tmp)%MOD;
            }
        }
    }
    return ret;
}
void init(){
    p2[0]=1;
    for (int i=1; i<maxn; i++)
        p2[i]=(p2[i-1]*2)%MOD;
}
int main(){
    init();
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        int x;
        scanf("%d", &x);
        while (x--) {
            int y;
            scanf("%d", &y);
            y--;
            int pos=(y-i+n)%n+1;
            a[pos]++;
            if (pos > 1)
                b[n+2-pos]++;
            else
                b[pos]++;
        }
    }
    printf("%lld\n", (work(a, 0)+work(b, 1))%MOD);
    return 0;
}
