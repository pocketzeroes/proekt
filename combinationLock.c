#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
ll a  [200005];
ll sum[200005];


int main(){
    int T;
    scanf("%d", &T);
    int cas=1;
    while(T--){
        int w;
        long long n;
        scanf("%d %lld", &w, &n);
        for(int i=1;i<=w;i++){
            scanf("%d", &a[i]);
        }
        qsort(a+1, w, sizeof(ll), cmpLL);
        for(int i=1;i<=w;i++){
            a[i+w]=a[i]+n;
        }
        sum[0]=0;
        for(int i=1;i<=2*w;i++){
            sum[i]=sum[i-1]+a[i];
        }
        int r=1;
        long long ans = (long long)1e18;
        for(int i=1;i<=w;i++){
            while(r<=i+w-1&&a[r]<=a[i]+n/2){
                r++;
            }
            long long tem = sum[r-1]-sum[i-1]-(r-i)*a[i]+(i+w-r)*a[i]-(sum[i+w-1]-sum[r-1]-(i+w-r)*n);
            ans = fminl(tem, ans);
        }
        printf("Case #%d: %lld\n", cas++, ans);
    }
    return 0;
}
