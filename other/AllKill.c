#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ mod = 998244353};
enum{ MAXN = 1000005 };
int n, t, a[MAXN];

int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
int main(){
    scanf("%d %d", &n, &t);
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]), a[i]--;
    int sum = accumulate(a, n);
    ll ret = t - n - sum + 1;
    for(int i=1; i<n; i++){
        sum -= a[i - 1];
        ret = ret * (t + 1 - sum) % mod;
    }
    printf("%lld\n", ret);
    return 0;
}
