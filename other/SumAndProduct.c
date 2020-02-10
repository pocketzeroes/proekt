#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define REP(i,s,t) for(int i=(s);i<(t);i++)
const ll INF=(ll)2E14;
enum{MAXN = 200005};
int endOne[MAXN], a[MAXN];
int main(){
    int n;
    scanf("%d", &n);
    REP(i, 0, n)
      scanf("%d", &a[i]);
    for (int i = n - 1; i >= 0; i--){
        if (a[i] == 1)
            endOne[i] = fmax(i, endOne[i + 1]);
        else
            endOne[i] = -1;
    }
    ll ans = 0;
    REP(i, 0, n){
        ll sum = a[i], prod = a[i];
        REP(j, i+1, n){
            if (a[j] == 1){
                int cntOne = endOne[j] - j + 1;
                if (prod > sum && cntOne >= prod - sum) 
                    ans++;
                sum += cntOne;
                j = endOne[j];
            }
            else {
                sum += a[j];
                if (prod > INF / a[j]) 
                    break;
                prod *= a[j];
                if (sum == prod) 
                    ans++;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
