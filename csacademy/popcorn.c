#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;
#define maxN 200011

typedef struct intrS {
    int l, r;
    ll val;
}intr;

int cmp(const void*pa,const void*pb){
    intr*me =(intr*)pa;
    intr*who=(intr*)pb;
    return(me->r < who->r)?-1:1;
}

int n, m, i, x;
intr I [maxN];
int dad[maxN];
int l  [maxN], r[maxN];
ll sum [maxN];
ll dif [maxN];
int cnt[maxN];
ll last;

int Find(int x) {
    if (x == dad[x]) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}
void check_comb(int id) {
    id = Find(id);
    while (true) {
        if (l[id] == 1) return;
        if (sum[id] <= 0) return;
        int bf = Find(l[id] - 1);
        dad[bf] = id;
        l[id] = l[bf];
        sum[id] += sum[bf];
    }
}
int check(ll delta) {
    int i, p;
    for (i = 0; i <= x + 1; i++) {
        dad[i] = l[i] = r[i] = i;
        sum[i] = 0;
        dif[i] = 0;
        cnt[i] = 0;
    }
    p = 1;
    for (i = 2; i <= x + 1; i++) {
        while (p <= n && I[p].r < i) {
            intr act = I[p++];
            dif[act.l] += act.val;
            dif[act.r + 1] -= act.val;
            sum[Find(act.l)] += act.val;
            sum[Find(act.r + 1)] -= act.val;
            check_comb(act.l);
        }
        int aux = Find(1);
        ll val = sum[aux] - delta;
        if (val < 0) continue;
        cnt[i] = cnt[r[aux]] + 1;
        dif[i] += val;
        dif[i + 1] -= val;
        sum[Find(i)] += val;
        sum[Find(i + 1)] -= val;
        check_comb(i);
        last = val;
    }
    return cnt[x + 1];
}
int main() {
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d %d %d", &I[i].l ,&I[i].r ,&I[i].val), I[i].val *= 2, I[i].r--;
    qsort(I + 1, n, sizeof(intr), cmp);
    x = I[n].r;
    ll delta = 0;
    for (ll step = 1LL << 32; step > 0; step >>= 1)
        if (check(delta + step) >= m)
            delta += step;
    if ((delta & 1)) delta++;
    check(delta);
    ll ans = (last + delta * m) / 2;
    printf("%lld\n", ans);
}





















































