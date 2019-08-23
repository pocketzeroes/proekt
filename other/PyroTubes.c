#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 250000};
int h[maxn + 5], data[maxn + 5], ret[maxn + 5];

inline bool reachable(int a, int b){
    int c = a ^ b;
    int cnt = 0;
    while(c){
        if (c & 1){
            cnt ++;
            if (cnt > 2)
                return false;
        }
        c >>= 1;
    }
    return true;
}
int main(){
    int t, n = 0;
    while(1){
        scanf("%d", &t);
        if (t == -1)
            break;
        data[n++] = t;
    }
    for (int i = n - 1; i >= 0; i--){
        int ans = h[data[i]];
        for (int j1 = 1; j1 <= maxn; j1 <<= 1){
            int t = data[i] ^ j1;
            if (t <= maxn)
                ans += h[t];
            for (int j2 = (j1 << 1); j2 <= maxn; j2 <<= 1){
                t = data[i] ^ j1 ^ j2;
                if (t <= maxn)
                    ans += h[t];
            }
        }
        ret[i] = ans;
        h[data[i]] += 1;
    }
    for (int i = 0; i < n; i++)
        printf("%d:%d\n", data[i], ret[i]);
    return 0;
}
