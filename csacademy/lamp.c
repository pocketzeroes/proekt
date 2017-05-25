#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

typedef struct pairS{
    ll first;
    ll second;
}Pair;
Pair newPair(ll a, ll b){
    Pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Pair *pushbackP(Pair *array, int *size, Pair value) {
    Pair *output = resizeArray(array, Pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	Pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


/////////////////////
enum{ N   =(int) 2e6 + 1};
enum{ INF =(int) 1e9 + 9};
enum{ B   =(int) 1e9 + 7};
int n, d;
Pair c;
Pair a[N];
vec q1[N], q2[N];
int t[N], u[N];

Pair ccw(Pair p) {
    return newPair(p.first - p.second, p.first + p.second);
}
Pair cw(Pair p) {
    return newPair(p.second + p.first, p.second - p.first);
}
void push(int x, int tl, int tr) {
    if (!u[x]) return;
    t[x] += u[x];
    if (tl < tr - 1) {
        u[(x << 1)] += u[x];
        u[((x << 1) | 1)] += u[x];
    }
    u[x] = 0;
}
void upd(int ql, int qr, int qd, int x, int tl, int tr) {
    push(x, tl, tr);
    if (qr <= tl || tr <= ql) return;
    if (ql <= tl && tr <= qr) {
        u[x] += qd;
        push(x, tl, tr);
        return;
    }
    int mid = (tl + tr) / 2;
    upd(ql, qr, qd, (x << 1), tl, mid);
    upd(ql, qr, qd, ((x << 1) | 1), mid, tr);
    t[x] = min(t[(x << 1)], t[((x << 1) | 1)]);
}
ll get() {
    int x = 1, tl = 1, tr = 2 * d + 2;
    while (tl < tr - 1) {
        push(x, tl, tr);
        int mid = (tl + tr) / 2;
        if (t[x] == t[(x << 1)] + u[(x << 1)]) x *= 2, tr = mid;
        else x = x * 2 + 1, tl = mid;
    }
    return tl - 1;
}
Pair poss(ll r) {
    for (int i = 1; i <= n; ++i) {
        ll lx = a[i].first - r, rx = a[i].first + r;
        lx = max(lx, 0ll), rx = min(rx, d * 2ll);
        if (lx > rx) continue;
        ll ly = a[i].second - r, ry = a[i].second + r;
        ly = max(ly, 0ll), ry = min(ry, d * 2ll);
        if (ly > ry) continue;
        q1[lx].ptr = pushbackP(q1[lx].ptr, &q1[lx].sz ,newPair(ly, ry));
        if (rx < 2 * d) 
            q2[rx+1].ptr = pushbackP(q2[rx+1].ptr, &q2[rx+1].sz ,newPair(ly, ry));
    }
    memset(t, 0, sizeof t);
    memset(u, 0, sizeof u);
    for (int i = 0; i <= (2 * d); ++i) {
        for(int z=0;z<q1[i].sz;z++){Pair q = q1[i].ptr[z];
            upd(q.first + 1, q.second + 2, +1, 1, 1, 2 * d + 2);
        }
        for(int z=0;z<q2[i].sz;z++){Pair q = q2[i].ptr[z];
            upd(q.first + 1, q.second + 2, -1, 1, 1, 2 * d + 2);
        }
        q1[i].sz=0, q2[i].sz=0;
        push(1, 1, 2 * d + 2);
        if (t[1] == 0) {
            for (int j = (i + 1); j <= (2 * d); ++j)
                q1[j].sz=0, q2[j].sz=0;
            return newPair(i, get());
        }
    }
    return newPair(INF, INF);
}
int main() {
    scanf("%d %lld %lld %d", &n, &c.first, &c.second, &d);
    c = ccw(c);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &a[i].first, &a[i].second);
        a[i] = ccw(a[i]);
        a[i].first -= c.first - d, a[i].second -= c.second - d;
    }
    ll l = 0, r = 1e10;
    while (l < r) {
        ll mid = (l + r + 1) / 2;
        if (poss(mid).first != INF) l = mid;
        else r = mid - 1;
    }
    Pair ans = poss(l);
    assert(0 <= ans.first && ans.first <= 2 * d && 0 <= ans.second && ans.second <= 2 * d);
    ans.first += c.first - d, ans.second += c.second - d;
    ans = cw(ans);
    
    printf("%lld %f %f\n", l + 1 , (ans.first / 2.0) , (ans.second / 2.0) );
    return 0;
}






















































