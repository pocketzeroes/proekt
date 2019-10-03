#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{  maxn=500000+5};
int a [maxn];
int dp[maxn];
int n;

int BinarySearch(int size,int k){
    int l=1,r=size;
    while(l<=r){
        int mid=(l+r)>>1;
        if(k>dp[mid])
            l=mid+1;
        else
            r=mid-1;
    }
    return l;
}
int LIS(){
    int ans=1,j;
    dp[1] = a[1];
    for(int i=2; i<=n; i++){
        if(a[i]<=dp[i])
            j=1;
        else if(a[i]>dp[ans])
            j=++ans;
        else
            j=BinarySearch(ans,a[i]);
        dp[j]=a[i];
    }
    return ans;
}
int main(){
    int T=1;
    while(T--){
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            scanf("%d", &a[i]);
        memset(dp,0,sizeof(dp));
        printf("%d\n", LIS());
    }
    return 0;
}
