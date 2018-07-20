#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;
int main(){
    ll n;
    scanf("%lld", &n);
    char s[n];
    scanf("%s", &s);
    ll a=-1, b=-1, c=-1, d=-1, m=0;
    for(ll i=0; i<n; i++){
        if(s[i]=='1'){
            if(a==-1)
                a=i;
            else if(b==-1)
                b=i;
            else if(c==-1){
                c=i;
                m=max(m,c+1)+1;
            }
            else if(d==-1)
                d=i;
            else{
                a=b;
                b=c;
                c=d;
                d=i;
            }
            if(d!=-1)
                m=max(m,d-a+1);
        }
    }
    m=max(m,n-b+1);
    if(d==-1){
        printf("%lld", max(c+1,n-a));
    }
    else
        printf("%lld", m-1);
    return 0;
}
