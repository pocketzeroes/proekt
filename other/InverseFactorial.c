#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000001];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
ll n, m, num, res, ans, len;
char*str;

int main(){
    str=getstr();
    len = strlen(str);
    if( len < 10 ){
        ll i = 1;
        ll ans = 1;
        while(1){
            ans *= i;
            if( ans == atoi(str)){
                printf("%lld", i);
                break;
            }
            i ++;
        }
    }
    else{
        ll i = 1;
        double ans = 1;
        while(1){
            ans += log10(i);
            if( floor(ans)==len ){
                printf("%lld", i);
                break;
            }
            i++;
        }
    }
    return 0;
}
