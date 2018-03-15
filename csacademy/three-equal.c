#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


int num[100010];

int xd(int ans,int n){
    int m = 0;
    for(int i=1;i<=n;i++){
        int k = num[i];
        while (k!=ans) {
            k = (k+1)%3;
            m++;
        }
    }
    return m;
}
int main(){
    int n; 
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%d",&num[i]);
    int minn = xd(0, n);
    minn = min(minn,xd(1,n));
    minn = min(minn,xd(2,n));
    printf("%d\n",minn);
    return 0;
}
