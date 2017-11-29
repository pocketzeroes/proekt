#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MAX = 410000};

ll a[MAX],p[MAX],t[MAX],last[MAX],slast[MAX],kl[MAX];

ll bs(int s,int e,ll x,int st){
    if(x<a[st])
        return 0;
    if(s==e)
        return (s-st)+1;
    int m=((s+e)/2)+1;
    if(p[m]-p[st]+(m-st)+a[st]>x)
        return bs(s,m-1,x,st);
    return bs(m,e,x,st);
}
int main(){
    ll n,w,h,s=0,sum=0;
    scanf("%lld %lld %lld",&n,&w,&h);
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
        sum+=a[i];
    }
    p[0]=a[0];
    for(int i=1;i<n;i++){
        p[i]=p[i-1]+a[i];
    }
    for(int i=0;i<n;i++){
        p[i+n]=p[i+n-1]+a[i];
        a[i+n]=a[i];
    }
    ll tol,te,tim=0;
    for(int i=1;i<=h;i++){
        tim=i;
        if(last[s%n]!=0){
            tol=i-last[s%n];
            te=s-slast[last[s%n]]+kl[last[s%n]];
            break;
        }
        last[s%n]=i;
        ll x=w/(sum+n);
        ll y=bs(s%n,2*n-1,w%(sum+n),s%n);
        s+=y+(x*n);
        kl[i]=y+(x*n);
        slast[i]=s;
        if(i==h){
            ll ans=s/n;
            if(s%n!=0)
                ans++;
            return printf("%lld\n",ans)*0;
        }
    }
    ll ba=0;
    for(int i=last[s%n];i<=last[s%n]+((h-tim+1)%tol)-1;i++)
        ba+=kl[i];
    ll ansi=ba+(s+(((h-tim+1)/tol)*te));
    ll ansi2=ansi/n;
    if(ansi%n!=0)
        ansi2++;
    printf("%lld\n", ansi2);
    return 0;
}
