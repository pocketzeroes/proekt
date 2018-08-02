#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper") 
#pragma GCC target("avx") 
#include <x86intrin.h> 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>
#include<stddef.h>
inline int max(int a,int b){return a>b?a:b;}
#define max3(a, b, c) ((a)>(b) ? ((a)>(c) ? (a) : (c)) : ((b)>(c) ? (b) : (c)))


enum{ maxN = 5 * (int)1e5 + 10};
int n, q;
typedef struct{
    int pref, suf, sum;
}node;
node t[4 * maxN];
int val[maxN];
int pref[maxN];
char buff[500000];

int getSum(int l, int r){
    return pref[r] - pref[l - 1];
}
void build(int v, int tl, int tr) {
    int tm = (tl + tr) / 2;
    if (tl == tr) {
        t[v].pref = max(0, val[tl]);
        t[v].suf = t[v].pref;
        t[v].sum = t[v].pref;
        return ;
    }
    build(v + v, tl, tm);
    build(v + v + 1, tm + 1, tr);
    t[v].pref = max(t[v + v].pref, getSum(tl, tm) + t[v + v + 1].pref);
    t[v].suf = max(t[v + v + 1].suf, getSum(tm + 1, tr) + t[v + v].suf);
    t[v].sum = max3(t[v + v].sum, t[v + v + 1].sum, t[v + v].suf + t[v + v + 1].pref);
}
int getpref(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr) {
        return t[v].pref;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) {
        return getpref(v + v, tl, tm, l, r);
    }
    if (l >= tm + 1) {
        return getpref(v + v + 1, tm + 1, tr, l, r);
    }
    return max(getpref(v + v, tl, tm, l, tm), getSum(tl, tm) + getpref(v + v + 1, tm + 1, tr, tm + 1, r));
}
int getsuf(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr) {
        return t[v].suf;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) {
        return getsuf(v + v, tl, tm, l, r);
    }
    if (l >= tm + 1) {
        return getsuf(v + v + 1, tm + 1, tr, l, r);
    }
    return max(getsuf(v + v + 1, tm + 1, tr, tm + 1, r), getSum(tm + 1, tr) + getsuf(v + v, tl, tm, l, tm));
}
int getmx(int v, int tl, int tr, int l, int r) {
    if (l == tl && r == tr) {
        return t[v].sum;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) {
        return getmx(v + v, tl, tm, l, r);
    }
    if (l >= tm + 1) {
        return getmx(v + v + 1, tm + 1, tr, l, r);
    }
    return max3(getmx(v + v, tl, tm, l, tm), getmx(v + v + 1, tm + 1, tr, tm + 1, r), 
                    getsuf(v + v, tl, tm, l, tm) + getpref(v + v + 1, tm + 1, tr, tm + 1, r));
}
int main(){
    scanf("%d", &n);
    scanf("%s", &buff);
    char*s=buff;
    scanf("%d", &q);
    for (int i = 0; s[i]; i++) {
        if (s[i] == 'C') 
            val[i + 1] = 1;
        else
            val[i + 1] = -1;
        pref[i + 1] = pref[i] + val[i + 1];
    }
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", getmx(1, 1, n, l, r) - getSum(l, r) );
    }
    return 0;
}
