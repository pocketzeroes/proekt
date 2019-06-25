#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int  K[100002];
char C[100002];

ll gcd(ll u, ll v){
  return v != 0LL ? gcd(v, u%v) : u;
}
int main(){
    int te;
    scanf("%d", &te);
    while(te--){
        ll sumw=0,
           sumb=0;
        int n;
        scanf("%d", &n);
        for(int i=0; i<n; i++){
            int  k;
            char c;
            scanf("%d %c", &k, &c);
            K[i]=k;
            C[i]=c;
            if(c=='W')
                sumw+=k;
            else
                sumb+=k;
        }
        if(sumw==0){
            printf("%lld\n", sumb);
            continue;
        }
        if (sumb==0){
            printf("%lld\n", sumw);
            continue;
        }
        ll d = gcd(sumw, sumb);
        sumw/=d;
        sumb/=d;
        ll w=0,b=0;
        int wyn=0;
        for(int i=0;i<n;i++){
            if (C[i]=='W'){
                if (b%sumb)
                    w+=K[i];
                else{
                    if (w/sumw<b/sumb && b/sumb<=(w+K[i])/sumw)
                        wyn++;
                    w+=K[i];
                }
            }
            else{
                if (w%sumw)
                    b+=K[i];
                else{
                    if (b/sumb<w/sumw && w/sumw<=(b+K[i])/sumb)
                        wyn++;
                    b+=K[i];
                }
            }
        }
        printf("%d\n", wyn);
    }
    return 0;
}
