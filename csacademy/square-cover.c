#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll m, n, kei;
ll height, width;
ll aa[333][333];
ll acnt[100010];
bool checked[100010];

void sayno() {
    puts("0");
    exit(0);
}
int main(){
    scanf("%lld %lld", &height, &width);
    for(ll y=0ll;y<(height);++y) {
        for(ll x=0ll;x<(width);++x) {
            ll a;
            scanf("%lld", &a);
            ++a;
            aa[y][x] = a;
            acnt[a] += 1;
        }
    }
    for(ll y=0ll;y<(height);++y) {
        for(ll x=0ll;x<(width);++x) {
            ll a = aa[y][x];
            if (a == -1) 
                continue;
            if (checked[a]) 
                sayno();
            checked[a] = 1;
            aa[y][x] = -1;
            ll s = 1;
            while (aa[y][x + s] == a) {
                for(ll i=0ll;i<(s);++i) {
                    if (aa[y + 1 + i][x + s] != a) 
                        sayno();
                    aa[y + 1 + i][x + s] = -1;
                }
                for(ll i=0ll;i<(s);++i) {
                    if (aa[y + s][x + i] != a) 
                        sayno();
                    aa[y + s][x + i] = -1;
                }
                aa[y][x + s] = -1;
                ++s;
            }
        }
    }
    puts("1");
    return 0;
}





