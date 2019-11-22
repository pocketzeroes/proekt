#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXN = 100000};

int n, peopl[MAXN], order[MAXN], islands[MAXN], ranks[MAXN];
bool alive[MAXN];

int fi(int a){
    if (islands[a] == a) 
        return a;
    islands[a] = fi(islands[a]);
    return islands[a];
}
bool un(int a, int b){
    a = fi(a);
    b = fi(b);
    if (a != b){
        if (ranks[a] <= ranks[b]){
            islands[a] = b;
            peopl[b] += peopl[a];
            if (ranks[a] == ranks[b])
                ranks[b]++;
        }
        else{
            islands[b] = a;
            peopl[a] += peopl[b];
        }
        return true;
    }
    return false;
}
int rup(int a) {
    return (a % 10) ? a + 10 - (a % 10) : a;
}
int main() {
    scanf("%d", &n);
    for(int i=0;i<(n);i++)
        scanf(" %d", &peopl[i]);
    for(int i=0;i<(n);i++) 
        scanf(" %d", &order[i]);
    for(int i=0;i<(n);i++) 
        islands[i] = i;
    ll maxchaos = 0LL;
    ll segments = 0LL;
    ll base_chaos = 0LL;
    for (int j = n - 1; j >= 0; j--){
        int i = order[j] - 1;
        alive[i] = true;
        segments++;
        base_chaos += rup(peopl[i]);
        for (int j = i - 1; j <= i + 1; j += 2){
            if (0 <= j && j < n && alive[j]) {
                base_chaos -= rup(peopl[fi(i)]);
                base_chaos -= rup(peopl[fi(j)]);
                un(i, j);
                segments--;
                base_chaos += rup(peopl[fi(i)]);
            }
        }
        maxchaos = fmaxl(maxchaos, base_chaos * segments);
    }
    printf("%lld\n", maxchaos);
    return 0;
}
