#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define N 100010
#define ll long long

int n,r[N],c[N],t[N];
char s[N];

void mod(int x){
    for (;x;x-=x&(-x))
        t[x]+=1;
}
int query(int x){
    int ans=0;
    for (;x<=n;x+=x&(-x))
        ans+=t[x];
    return ans;
}
int main(){
    scanf("%d",&n);
    scanf("%s",s);
    for (int i=1;i<=n;i++)
        scanf("%d",&r[i]);
    for (int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    ll ans=0;
    for (int i=0;i<n;i++){
        int x=(s[i]=='1');
        x+=query(i+1);
        if (x&1)
            ans+=c[i+1],mod(r[i+1]);
    }
    printf("%lld\n",ans);
    return 0;
}


















































