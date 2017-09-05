#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
    int n, arr[100005];
    scanf("%d", &n);
    ll sum    = 0;
    ll neg_mx =-1;
    ll pos_mx = 0;
    for(int i=1; i<=n; i++){
        scanf("%d", &arr[i]);
        sum += abs(arr[i]);
    }
    printf("%lld\n", sum);
    int cnt = 1;
    for(int i=n; i>=1; i--){
        if(arr[i]*cnt >= 0)
            continue;
        else{
            printf("%d ", i);
            if( cnt == 1) 
                cnt = -1;
            else if(cnt == -1) 
                    cnt =   1;
        }
    }
    return 0;
}






















