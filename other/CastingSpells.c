#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define mid ((l+r)>>1)

enum{ MAXN = 300010};
char st[MAXN];
int u[MAXN << 1], mx[MAXN][19];
int Log[MAXN];

inline int max(int x, int y){
    return x ^ ((x ^ y) & -(x < y));
}
inline int min(int x, int y) {
    return y ^ ((x ^ y) & -(x < y));
}
void manacher(const char *s, int u[], int n){
    for (int i = 0; i < 2 * n; ++ i)
        u[i] = 1;
    for (int i = 1, x = 0; i < n *2 -1; ++ i){
        u[i] = max(x + u[x] - i, 1 - i % 2);
        if (x + x >= i)
            u[i] = min(u[i], u[x + x - i]);
        int a = (i - 1 - u[i]) >> 1, b = (i + 1 + u[i]) >> 1;
        while(a >= 0 && b < n && s[a] == s[b]){
            a--, b++, u[i] += 2;
        }
        if (i + u[i] > x + u[x])
            x = i;
    }
    u[0] = 0;
    for (int i = 1; i <n; ++ i)
        u[i] = u[2 * i - 1] / 2;
}
void build_st(int n){
    for (int i = 0; i < n; ++ i)
        mx[i][0] = u[i] + i;
    for (int j = 1, l = 2; (1 << j) < n; ++ j, l <<= 1){
        for (int i = 0; i + l - 1 < n; ++ i){
            mx[i][j] = max(mx[i][j - 1], mx[i + (l >> 1)][j - 1]);
        }
    }
}
int range(int l, int r){
    int j = Log[r - l + 1];
    return max(mx[l][j], mx[r - (1 << j) + 1][j]);
}
int query(int l, int r, int x){
    if (l == r)
        return l;
    int lm = range(l, mid), rm = range(mid + 1, r);
    if (lm >= x)
        return query(l, mid, x);
    else if(rm >= x)
        return query(mid + 1, r, x);
    else
        return -1;
}
int main(){
    for(int i = 1; i < MAXN; ++ i)
        Log[i] = 31 - __builtin_clz(i);
    int T=1;
    while(T --){
        scanf("%s", st);
        int n = strlen(st);
        manacher(st, u, n);
        build_st(n);
        int ret = 0;
        for(int i = 0; i < n; ++ i){
            int R = u[i];
            if (R < 2) 
                continue;
            int j = query(i - R / 2, i - 1, i);
            if (j != -1)
                ret = max(ret, i - j);
        }
        printf("%d\n", ret * 4);
    }
    return 0;
}
