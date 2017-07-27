#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

long long ans = 1;
long long n;

int main(){
    scanf("%lld", &n);
    int vine=(0);
    while (n >= 10) {
        int c = n % 10 - vine;
        n /= 10;
        int transp;
        scanf("%d", &transp);
        vine = transp;
        if (transp)
            c += 10;
        if (c < 10)
            ans *= c + 1;
        else
            ans *= 19 - c;
    }
    n -= vine;
    ans *= n + 1;
    printf("%lld", ans);
    return 0;
}
