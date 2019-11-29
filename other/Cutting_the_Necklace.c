#pragma GCC optimize "-O3" // https://open.kattis.com/problems/cuttingthenecklace
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
    int k, n;
    scanf("%d %d", &k, &n);
    ll a[n  ]; clr(a);
    ll p[n+1]; clr(p);
    ll tot = 0;
    ll mx  = 0;
    for(int z=0;z<n;z++){
        scanf("%lld", &a[z]);
        tot +=   a[z];
        mx = fmax(mx, a[z]);
    }
    if(tot % k != 0){
        puts("NO");
        return 0;
    }
    ll goal = tot / k;
    if(mx > goal){
        puts("NO");
        return 0;
    }
    p[0] = 0;
    for(int i = 0; i < n; ++i)
        p[i + 1] = p[i] + a[i];
    ll dp[n+1]; fill(dp, n+1, -1);
    for(int i = n - 1; i >= 0; --i){
        if(a[i] == goal){
            dp[i] = 1;
            if(dp[i + 1] != -1)
               dp[i] += dp[i + 1];
        }
        else if (p[n] - p[i] < goal)
            continue;
        else {
            int lo = i + 1;
            int hi = n;
            while (lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if (p[mid] - p[i] >= goal)
                    hi = mid;
                else
                    lo = mid;
            }
            if (p[hi] - p[i] == goal) {
                dp[i] = 1;
                if (dp[hi] != -1)
                    dp[i] += dp[hi];
            }
        }
    }
    bool valid = dp[0] == k;
    for (int i = 1; i < n; ++i)
        valid |= dp[i] == k - 1;
    puts(valid ? "YES" : "NO");
    return 0;
}
