#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int n, m, v[1010], Path[1010];
ll D[1010];

typedef struct{
    int l, r, ck, t;
    ll S;
}Query;
Query w[1010];
typedef struct{
    int a, b;
    ll t, u;
}Edge;
Edge E[10100];
int EC;

Edge newEdge(int a, int b, ll t, ll u){
    Edge rez;
    rez.a=a;
    rez.b=b;
    rez.t=t;
    rez.u=u;
    return rez;
}
void Put0(int b, int e, ll t, ll d){
    E[EC++] = newEdge( b, e + 1,t, d );
}
void Put1(int b, int e, ll t, ll d){
    E[EC++] = newEdge( e + 1, b,-t, -d);
}
int Calc(ll SS){
    int i;
    EC = 0;
    for (i = 0; i < m; i++) {
        ll t = w[i].S - w[i].t*SS;
        ll tt = (w[i].t + 1)*SS - w[i].S;
        if (t < 0) {
            if (w[i].ck == 0)return 2;
        }
        if (tt < 0) {
            if (w[i].ck == 1)return 1;
        }
        int b = w[i].l%n, e = w[i].r%n;
        if ((e + 1) % n == b) {
            if (w[i].ck == 0) {
                if (t < 0)return 2;
            }
            if (w[i].ck == 1) {
                if (t > 0)return 1;
            }
            continue;
        }
        if (w[i].ck == 0) {
            if (b <= e) {
                if (t < 0)return 2;
                Put0(b, e, t, -w[i].t);
            }
            else {
                t = (w[i].t + 1)*SS - w[i].S;
                Put1(e + 1, b - 1, t, w[i].t + 1);
            }
        }
        if (w[i].ck == 1) {
            if (b <= e) {
                Put1(b, e, t, -w[i].t);
            }
            else {
                t = (w[i].t + 1)*SS - w[i].S;
                if (t < 0)return 1;
                Put0(e + 1, b - 1, t, w[i].t + 1);
            }
        }
    }
    E[EC++] = newEdge( 0,n,SS ,  1 );
    E[EC++] = newEdge( n,0,-SS, -1 );
    for (i = 0; i < n; i++) {
        E[EC++] = newEdge( i + 1,i,-1, 0);
    }
    for (i = 0; i <= n; i++)D[i] = 1e15;
    int ck = 0, x = 0;
    for (i = 0; i <= n; i++) {
        for (int j = 0; j < EC; j++) {
            if (D[E[j].b] > D[E[j].a] + E[j].t) {
                D[E[j].b] = D[E[j].a] + E[j].t;
                Path[E[j].b] = j;
                ck = i;
                x = E[j].b;
            }
        }
    }
    for (i = 0; i <= n; i++)v[i] = 0;
    if (ck == n) {
        ll sss = 0;
        while (!v[x]) {
            v[x] = 1;
            x = E[Path[x]].a;
        }
        int st = x;
        ll s2 = 0;
        while (1) {
            sss += E[Path[st]].u;
            st = E[Path[st]].a;
            s2 += E[Path[st]].t;
            if (st == x)break;
        }
        if (s2 >= 0) {
            while (1) {}
        }
        if (sss > 0)return 1;
        return 2;
    }
    return 0;

}
int main(){
    int i, chk = 0, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d%lld", &w[i].l, &w[i].r, &w[i].ck, &w[i].S);
        w[i].t = (w[i].r - w[i].l + 1) / n;
        if (!w[i].ck) {
            if (w[i].t)chk = 1;
            else {
                for (j = w[i].l; j <= w[i].r; j++)v[j%n] = 1;
            }
        }
    }
    for (i = 0; i < n; i++)if (!v[i])break;
    if (i != n && !chk) {
        printf("-1\n");
        return 0;
    }
    int b = 0, e = 1000000000, rr = -1;
    while (b <= e) {
        int mid = (b + e) >> 1;
        int t = Calc(mid);
        if (t == 0) {
            rr = mid;
            break;
        }
        else if (t == 1) {
            b = mid + 1;
        }
        else if (t == 2) {
            e = mid - 1;
        }
    }
    if (rr == -1) {
        printf("0\n");
        return 0;
    }
    b = 0, e = rr - 1;
    int br = rr, er = rr;
    while (b <= e) {
        int mid = (b + e) >> 1;
        if (!Calc(mid)) {
            br = mid;
            e = mid - 1;
        }
        else b = mid + 1;
    }
    b = rr + 1, e = 1000000000;
    while (b <= e) {
        int mid = (b + e) >> 1;
        if (!Calc(mid)) {
            er = mid;
            b = mid + 1;
        }
        else
            e = mid - 1;
    }
    printf("%d\n", er - br + 1);
    return 0;
}
