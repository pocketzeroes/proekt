#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

inline int nxt() {
    int x;
    scanf("%d", &x);
    return x;
}
int ask(int x) {
    printf("%d", x);
    fflush(stdout);
    return nxt();
}
void solve() {
    if (ask(0)) {
        if (ask(11)) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j)
                    ask((5 + i) * 10 + (5 + j));
            }
        } 
        else {
            int cnt = ask(91) + ask(1);
            if (cnt == 1) {
                for (int i = 0; i < 7; ++i)
                    ask(21 + i * 10);
            } 
            else {
                cnt = 0;
                int x = -1, y = -1;
                int ls = 1;
                for (int i = 0; i < 6; ++i) {
                    int tmp = ask(21 + i * 10);
                    if (ls == 0 && tmp == 0) {
                        x = 11 + i * 10;
                        y = 21 + i * 10;
                    }
                    ls = tmp;
                    cnt += tmp;
                }
                if (cnt == 0)
                    ask(10);
                else
                    ask(x + 1);
            }
        }
        return;
    }
    int cnt = 0;
    int rem = 10;
    int black = -1;
    for (int i = 1; i < 10; ++i) {
        int x = ask(i);
        --rem;
        cnt += x;
        if (x)
            black = i;
        if (cnt == 2)
            break;
    }
    if (cnt == 1)
        ask(black + 10);
    else {
        for (int i = 90; rem; --rem, i -= 10)
            ask(i);
    }
}
int main() {
    int T = nxt();
    while (T--)
        solve();
    return 0;
}

































