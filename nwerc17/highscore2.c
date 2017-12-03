#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
typedef long long ll;
ll max(ll a, ll b){return a>b?a:b;}


ll score (ll a, ll b, ll c){   
    return a*a+b*b+c*c+7*a;
}
int main(){
    int n, t;
    ll a, b, c, d, m, maxscore;
    scanf("%d", &n);
    for (t = 0; t < n; t++){
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        if (a>b) swap(a,b);
        if (a>c) swap(a,c);
        if (b>c) swap(b,c);
        maxscore = score(a, b, c+d);
        for (m = a+1; m <= b && m <= a+d && m <= a+3; m++)
            maxscore = max(maxscore, score(m, b, c+d+a-m));
        for (m = b; 2*m <= a+b+d && 3*m <= a+b+c+d && m <= a+3; m++)
            maxscore = max(maxscore, score(m, m, a+b+c+d-2*m));
        printf("%lld\n", maxscore);
    }
}
