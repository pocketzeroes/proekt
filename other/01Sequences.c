#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
enum{ mod = 1000000007};

ll power(ll a, ll b){
    if (b <= 0) 
        return 1;
    ll temp = power(a, b / 2) % mod;
    if (b % 2 == 0)
        return (temp * temp) % mod;
    else
        return (((a * temp) % mod) * temp) % mod;
}
int range;
int* fact;
int*ifact;

void calcFacts(){
    fact[0] = 1;
    for(ll i = 1; i <= range; ++i)
        fact[i] = (1LL*fact[i-1]*i)%mod;
    ifact[range] = power(fact[range], mod-2);
    for(int i = range-1; i >= 0; --i)
        ifact[i] = (1LL*ifact[i+1]*(i+1))%mod;
}
void NchooseK(){
    range = (int)1e6;
    fact =calloc(range+1, sizeof(int));
    ifact=calloc(range+1, sizeof(int));
    calcFacts();
}
int choose(int n, int k){
    if(k < 0 || k > n || n < 0)
        return 0;
    return((1LL*fact[n]*ifact[k])%mod * 1LL*ifact[n-k])%mod;
}
ll triangle(ll num) {
    if (num <= 0)
        return 0;
    return(num * (num + 1) / 2)%mod;
}
int main(){
    NchooseK();
    char*sequence=getstr();
    ll length = strlen(sequence), iSum = 0, qSum = 0, firstPartOfSum = 0, secondPartOfSum = 0;
    int iCount = 0, k = 0;
    for (int i = 0; i < length; i++){
        if (sequence[i] == '1'){
            iCount++;
            iSum += length - 1 - i;
        }
        if (sequence[i] == '?'){
            k++;
            qSum += length - 1 - i;
        }
    }
    iSum%=mod;
    qSum%=mod; 
    firstPartOfSum = (iSum * power(2, k))%mod;
    firstPartOfSum += (qSum * power(2, k - 1))%mod;
    firstPartOfSum %= mod;
    for (ll i = 0; i <= k; i++){
        secondPartOfSum += (choose(k, i) * triangle(i + iCount - 1))%mod;
        secondPartOfSum %= mod;
    }
    printf("%lld\n", (firstPartOfSum - secondPartOfSum + mod)%mod);
    return 0;
}
