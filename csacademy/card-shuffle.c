#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include<limits.h>

int64_t a[100005];

void solve(){
    int64_t i,j,n,k;
    scanf("%d %d",&n,&k);
    if(n%2==0){
        if(k%4==1){
            i=2;
            for(j=1;j<=n;j+=2){
                a[j]=i;
                i+=2;
            }
            i=n-1;
            for(j=2;j<=n;j+=2){
                a[j]=i;
                i-=2;
            }
        }
        else if(k%4==2){
            i=n-1;
            for(j=1;j<=n;j+=2){
                a[j]=i;
                i-=2;
            }
            i=n;
            for(j=2;j<=n;j+=2){
                a[j]=i;
                i-=2;
            }
        }
        else if(k%4==3){
            i=n;
            for(j=1;j<=n;j+=2){
                a[j]=i;
                i-=2;
            }
            i=1;
            for(j=2;j<=n;j+=2){
                a[j]=i;
                i+=2;
            }
        }
        else{
            for(j=1;j<=n;j++) 
                a[j]=j;
        }
        for(i=1;i<n+1;i++) 
            printf("%d ", a[i]);
    }
    else{
        if(k%2==0){
            for(i=1;i<n+1;i++) 
                printf("%d ",i);
        }
        else{
            i=n;
            for(j=1;j<=n;j+=2){
                a[j]=i;
                i-=2;
            }
            i=2;
            for(j=2;j<=n;j+=2){
                a[j]=i;
                i+=2;
            }
            for(i=1;i<n+1;i++) 
                printf("%d ",a[i]);
        }
    }
}
int main(){
    int64_t t=1;
    while(t--){
        solve();
    }
    return 0;
}
























































