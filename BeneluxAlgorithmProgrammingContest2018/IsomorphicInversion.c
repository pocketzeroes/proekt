#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define mod 1000000007ll
int P =(int) 1e5 + 1;

bool isprime(int N){
    for(int i = 2; i  * i <= N; i++) 
        if(N % i == 0)
            return false;
    return true;
}
char buff[10000000];
int main(){
    while(!isprime(P))
        P += 2;
    scanf("%s", &buff);
    int ret = 0, i, j;
    ll hl = 0, hr = 0, pr = 1;
    int buflen = strlen(buff);
    fprintf(stderr, "buf len = %d\n", buflen);
    for(i=0, j=buflen-1; i<j; i++, j--){
        hl = (P * hl +  buff[i]) % mod;
        hr = (hr + pr * buff[j]) % mod;
        pr = (pr * P) % mod;
        if (hl == hr){
            ret += 2;
            hl = hr = 0;
            pr = 1;
        }
    }
    if(i == j || hl != hr)
        ret++;
    printf("%d\n", ret);
    return 0;
}
