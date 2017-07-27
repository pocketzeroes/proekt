#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}



#define ll long long
#define str string
#define fi first
#define se second
#define pb push_back
#define SET(a, b) memset(a, b, sizeof(a))
#define inf 1000000000
#define mod 1000000007
#define eps 1e-6
#define PI atan(1) * 4

pair num[100005];
int  bit[100005];
int  maxx = 100000;
int  lft[100005], rgt[100005];
int  seg[262200], lazy[262200];
int  y, z, w;

void updbit (int i, int v) {
    if (i > maxx) return;
    bit[i] += v;
    updbit(i + (i & (-i)), v);
    return;
}
int qbit (int i) {
    return ((i <= 0) ? 0 : bit[i] + qbit(i - (i & (-i))));
}
void updseg (int l, int r, int i) {
    if (lazy[i] != 0) {
        seg[i] += lazy[i];
        if (l < r) {
            lazy[i * 2] += lazy[i]; lazy[i * 2 + 1] += lazy[i];
        }
        lazy[i] = 0;
    }
    if (r < y || l > z) return;
    if (y <= l && r <= z) {
        seg[i] += w;
        if (l < r) {
            lazy[i * 2] += w; lazy[i * 2 + 1] += w;
        }
        return;
    }
    int m = ((l + r) >> 1);
    updseg(l, m, i * 2); updseg(m + 1, r, i * 2 + 1);
    seg[i] = min(seg[i * 2], seg[i * 2 + 1]);
    return;
}
int qseg (int l, int r, int i) {
    if (lazy[i] != 0) {
        seg[i] += lazy[i];
        if (l < r) {
            lazy[i * 2] += lazy[i]; lazy[i * 2 + 1] += lazy[i];
        }
        lazy[i] = 0;
    }
    if (l == r) return l;
    int m = ((l + r) >> 1);
    int res;
    if (seg[i * 2] + lazy[i * 2] == 0) res = qseg(l, m, i * 2);
    else res = qseg(m + 1, r, i * 2 + 1);
    seg[i] = min(seg[i * 2], seg[i * 2 + 1]);
    return res;
}
int main() {
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q;
    scanf("%d %d", &a, &b);
    SET(bit, 0);
    for (i = 1; i <= a; i++) {
        scanf("%d", &num[i].fi); c = num[i].fi;
        num[i].se = qbit(max(c - b - 1, 0)) + i - 1 - qbit(min(c + b, maxx));
        updbit(c, 1);
    } 
    qsort(num+1, a, sizeof(pair), cmpP);
    for (i = 1, j = 1; i <= maxx; i++) {
        while (j <= a && num[j].fi < i) j++;
        lft[i] = j;
    }
    lft[maxx + 1] = a + 1;
    for (i = maxx, j = a; i >= 1; i--) {
        while (j >= 1 && num[j].fi > i) j--;
        rgt[i] = j;
    }
    rgt[0] = 0;
    SET(lazy, 0);
    for (i = 0; i < 262200; i++) seg[i] = inf;
    for (i = 1; i <= a; i++) {
        seg[i + 131071] = num[i].se;
    }
    for (i = 131071; i >= 1; i--) {
        seg[i] = min(seg[i * 2], seg[i * 2 + 1]);
    }
    for (i = 1; i <= a; i++) {
        c = qseg(1, 131072, 1);
        printf("%d%c", num[c].fi, (i == a) ? '\n' : ' ');
        y = 1; z = rgt[max(num[c].fi - b - 1, 0)]; w = -1;
        updseg(1, 131072, 1);
        y = lft[min(num[c].fi + b + 1, maxx + 1)]; z = a; w = -1;
        updseg(1, 131072, 1);
        y = z = c; w = inf;
        updseg(1, 131072, 1);
    }
    return 0;
}





















































