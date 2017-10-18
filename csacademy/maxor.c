#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stddef.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ N   =(int) (1<<19) +7};
enum{ MOD =(int) 1e9+7     };

int    a[N];
double h[N];
int n,m;


inline int read(){
    int x = 0,f=1;char c=getchar();
    for(;c<'0'||'9'<c;c=getchar())if(c == '-') f=-1;
    for(;'0'<=c&&c<='9';c=getchar())x=(x<<3)+(x<<1)+c-'0';
    return x*f;
}
void FWT(double a[],int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                double first=a[i+j],second=a[i+j+d];
                a[i+j+d]=first+second;
            }
}
void UFWT(double a[],int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                double first=a[i+j],second=a[i+j+d];
                a[i+j+d]=second-first;
            }
}
void solve(double a[],int n){
    FWT(a,n);
    for(int i=0;i<n;i++) 
        a[i]=a[i]*a[i];
    UFWT(a,n);
}
int main(){
    while(~scanf("%d",&n)){
        memset(h,0,sizeof(h));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            h[a[i]]++;
        }
        int len = (1<<17);
        solve(h,len);
        for(int i=1;i<=n;i++){
            h[(a[i]|a[i])] -- ;
        }
        for(int i=(1<<17)-1;i>=0;i--){
            if(h[i]>0){
                ll ans = h[i];
                printf("%d %lld\n",i,ans/2);
                break;
            }
        }
    }
    return 0;
}
























