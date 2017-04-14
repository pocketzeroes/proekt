#include<stdio.h>


enum{ nmax = 100010};
int n, k, cnt[nmax], top;
char st[nmax];
char s[200000];

int main() {
    scanf("%d %d", &n,&k);
    scanf("%s",&s);
    st[0] = ' ';
    for (int i = 0; s[i] ; ++ i) {
        st[++top] = s[i];
        if (st[top] == st[top - 1]) {
            cnt[top] = cnt[top - 1] + 1;
        } else {
            cnt[top] = 1;
        }
        while (cnt[top] == k) {
            top -= k;
        }
    }
    for (int i = 1; i <= top; ++ i) {
        putchar(st[i]);
    }
}
