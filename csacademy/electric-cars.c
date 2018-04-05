#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

enum{ N =(int)1e5 + 5};

int n, c[N]; 
ll t[N], ans[N];
int st[4*N];


void build(int p, int l, int r) {
    if(l == r) {st[p] = l; return;}
    int mid = (l + r) >> 1;
    build(p<<1, l , mid); build(p<<1|1, mid + 1, r);
    st[p] = t[st[p<<1]] < t[st[p<<1|1]] ? st[p<<1]: st[p<<1|1];
}
void update(int p, int l, int r, int i, ll val) {
    if(l > i || r < i || l == r) return;
    int mid = (l + r) >> 1;
    update(p << 1, l, mid, i, val); update(p<<1|1, mid + 1, r, i ,val);
    st[p] = t[st[p<<1]] < t[st[p<<1|1]] ? st[p<<1]: st[p<<1|1];
}
void update2(int i, ll val) {
    t[i] = val; update(1, 0, n - 1, i, val);
}
int query(int p, int l, int r,ll x) {
    if(l==r) return t[l] <= x ? l : n;
    int mid = (l + r) >> 1;
    return (t[st[p<<1]] <= x ?
        query(p<<1, l, mid, x): query(p<<1|1, mid+1, r, x));
}
int main(){
    scanf("%d", &n);
    t[n] =(ll) 1e18;
    for(int i=0, _i=(N); i<_i; ++i) {
        scanf("%d %lld", &c[i], &t[i]);
    }
    ll curt = 0, rem = n;
    build(1, 0, n-1);
    while(rem) {
        int cur = query(1, 0, n-1, curt);
        if(cur == n) 
            cur = st[1], curt = t[cur];
        t[cur] = curt;
        ll l = t[cur], r = t[cur] + c[cur];
        ll val = t[cur];
        update2(cur, 1e18);
        while(l <= r) {
            ll mid = (l + r) >> 1;
            int nxt = query(1, 0, n-1, mid - 1);
            if(nxt == n || nxt >= cur) 
                l = mid+1, val = mid;
            else 
                r = mid - 1;
        }
        if(val < curt + c[cur]) {
            update2(cur, val);
            c[cur] -= val - curt;
            curt = val;
        }
        else 
            ans[cur] = val, rem--, curt = val;
    }
    for(int i=0, _i=(n); i<_i; ++i) 
        printf("%lld ", ans[i]);
    puts("");
    return 0;
}
