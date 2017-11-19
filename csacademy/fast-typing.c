#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
char buff[100000];
int main(){
    char*s;
    ll n, c[30], tot=0;
    scanf("%s", &buff);
    s = strdup(buff);
    n = strlen(s);
    for(ll i=0; i<26; i++)
        scanf("%lld", &c[i]);
    for(ll i=0; i<n ; i++)
        tot += c[s[i]-'a'];
    printf("%lld\n", tot);
}
