#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
const double eps = 1e-6;
const int MINN   = 0xc0c0c0c0;
enum{ maxn   =(int) 1e4 + 5};
int arr[maxn];
int n, k;

bool check(double mid){
    int sum = 0;
    for (int i = 0; i < k; i++){
        int temp = (int)(1.0 * arr[i] / mid);
        if (fabs(1.0 * temp * mid - 1.0 * arr[i]) <= eps)
            temp--;
        sum += temp;
    }
    if (sum >= n)
        return true;
    return false;
}
int main(){
    scanf("%d%d", &k, &n);
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < k; i++)
        scanf("%d", &arr[i]);
    double l = 0, r = (double)n;
    double mid;
    double MAX = MINN;
    while (r - l >= eps){
        mid = (l + r) / 2.0;
        if (check(mid)){
            MAX = fmax(MAX, mid);
            l = mid;
        }
        else
            r = mid;
    }
    ll ans = 0;
    for (int i = 0; i < k; i++){
        int temp = (int)(1.0 * arr[i] / MAX);
        if (fabs(1.0 * temp * MAX - 1.0 * arr[i]) <= 1e-1)
            temp--;
        ans += temp;
    }
    printf("%lld\n", ans);
    return 0;
}
