#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;


ll n,a[100005];
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
    }
    a[0]=0, a[n+1]=100001;
    ll st=-1,ed=-1;
    for(ll i=n,j;i>0;i--) {
        if(a[i]!=a[i+1]) {
            if(st==-1)
                ed=i;
        }
        if(a[i]<=a[i+1]&&a[i]>=a[i-1])
            continue;
        if(st!=-1)   {
            printf("0");
            return 0;
        }
        for(j=i-1; j>0; j--)   {
            if(a[j]<a[j+1])
                break;
        }
        st=j+1;
        i=j+1;
        if(a[st]>a[ed+1])   {
            printf("0");
            return 0;
        }
        if(a[ed]<a[st-1])  {
            printf("0");
            return 0;
        }
    }
    ll t=0;
    if(st==-1)  {
        st=1,ed=1;
        ll cnt=0;
        for(int i=1;i<=n;i++)   {
            if(a[i]!=a[i-1])       {
                t+=(cnt*(cnt+1))/2;
                cnt=1;
            }
            else cnt++;
        }
        t+=(cnt*(cnt+1))/2;
    }
    else t=1;
    printf("%lld\n%lld %lld\n",t,st,ed);
}
