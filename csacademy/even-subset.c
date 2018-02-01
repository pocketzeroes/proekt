#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll max(ll a, ll b){return a>b?a:b;}

int cmpR(const void*pb, const void*pa){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return *a < *b ? -1 : 1;
}
int main(){
    int n;
    scanf("%d", &n);
    int arr[100005], x;
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), cmpR);// reverse
    ll mx  = 0;
    ll sum = 0;
    for(int i=0; i<n; i++){
        if(arr[i] < 0 && i&1^1)
            break;
        if(i&1)
            sum += arr[i]+arr[i-1];
        if(i&1)
            mx = max(mx, sum);
    }
    printf("%lld\n", mx);
    return 0;
}
