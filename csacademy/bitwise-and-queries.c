#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int q;
long long a, b, x;
inline long long f(long long a, long long x) {
    if (a  < x) 
        return 0ll;
    long long res = 0ll;
    int fix = 0;
    for (int i = 0; i < 63; i++) if (x & (1ll << i)) {
        fix++;
    }
    for (int i = 62; i >= 0; i--) {
       if (x & (1ll << i)) {
           fix--;
           if (a & (1ll << i)) 
               continue;
           return res;
       } 
       else if (a & (1ll << i)) {
          res += 1ll << (i - fix);
       }       
    }
    return res + 1;
}
int main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%lld %lld %lld", &a, &b, &x);
        printf("%lld\n", f(b, x) - f(a - 1, x));
    }
    return 0;
}
