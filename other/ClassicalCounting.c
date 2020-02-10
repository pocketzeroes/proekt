#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXN=100005    };
enum{ MOD=1000007    };
enum{ m1=29, m2=34483};
ll J[MAXN];

void build(int p){
    J[0]=1;
    for(int i=1;i<MAXN;i++)
        J[i]=(ll)J[i-1]*i%p;
}
int inv(int b, int p){
    if(b==1)
        return 1;
    return(ll)inv(p%b,p)*(p-p/b)%p;
}
ll C(int n,int m,int p){
    if(m<0||m>n)
        return 0;
    if(n>=p||m>=p)
        return(ll)C(n/p,m/p,p)*C(n%p,m%p,p)%p;
    return J[n]*inv((ll)J[m]*J[n-m]%p,p)%p;
}
ll H(int n,int m,int p){
    return C(n+m-1,m,p);
}
int N,M,K;
ll solve(const int p){
    build(p);
    ll ans=0;
    for(int i=0;i*(M+1)<=K;i++){
        ll tmp=C(N,i,p)*H(N,K-i*(M+1),p)%p;
        if(i%2==0)
            ans+=tmp;
        else
            ans-=tmp;
    }
    ans%=p;
    if(ans<0)
        ans+=p;
    return ans;
}
int main(){
    scanf("%d%d%d",&N,&M,&K);
    ll a1=solve(m1);
    ll a2=solve(m2);
    while(a2%m1!=a1)
        a2+=m2;
    printf("%lld\n", a2);
    return 0;
}


