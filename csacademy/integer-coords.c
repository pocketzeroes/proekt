#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll m[112][112];

int main(){
    ll l, c;
    scanf("%lld %lld", &l, &c);
    l++, c++;
    ll k;
    scanf("%lld", &k);
    for(ll i=0; i<l; i++)
        for(ll j=0; j<c; j++)
            m[i][j] = -1;
    m[0][0] = 0;
    for(ll i=0; i<l; i++){
        for(ll j=0; j<c; j++){
            if(m[i][j] == -1){
                ll num = 1;
                m[i][j] = 2;
                while(num*i<l && num*j<c){
                    num++;
                    m[num*i][num*j] = m[(num-1)*i][(num-1)*j]+1;
                }
            }
        }
    }
    ll resp=0;
    for(ll i=0; i<l; i++){
        for(ll j=0; j<c; j++){
            if(m[i][j] == k){
                resp += (l-i)*(c-j);
                if(i != 0 && j != 0)
                    resp += (l-i)*(c-j);
            }
        }
    }
    printf("%lld\n", resp);
    return 0;
}
