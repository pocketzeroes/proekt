#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
typedef long long ll;

enum{ N =(int) 1e5+500};
enum{ p =(int) 1e9+7  };
int n,q,mx,s[N];
ll f[N],sum[N];

int main(){
    n = read();
    q = read();
    for(register int i =1 ;i <= q; ++ i){
        int x,y;
        x=read();
        y=read();
        s[y] = max(s[y], x);
    }
    f[0] = 1,sum[0] = 1;
    for(register int i =1 ;i <= n + 1; ++ i){
        mx = max(mx,s[i - 1]);
        f[i] = (sum[i - 1] - (mx > 0 ? sum[mx - 1] : 0) + p) % p;
        sum[i] = (f[i] + sum[i - 1]) % p;
    }
    printf("%lld\n", f[n + 1]);
    return 0;
}
