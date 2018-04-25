#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b)do{ int tmp; tmp = a; a = b; b = tmp; }while(0);

typedef long long ll;
enum{ K = 12   };
enum{ N = 1010 };
enum{ M = 20020};
int n;
int a[K][N];
int ans[M];
int ansSz;
int p[N];

void precalc(){
    for (int k = 0; k < K; k++)
        for (int i = 1; i <= n; i++)
            a[k][i] = i;
    swap(a[K - 1][1], a[K - 1][2]);
    for (int x = 2; x < n && x <= 11; x++) {
        int y = (x - 2) / 10 + 1;
        bool ok = false;
        for (int k = 0; !ok && k < K - 1; k++) {
            if (a[k][y + 1] == y + 1) {
                swap(a[k][y + 1], a[k][x + 1]);
                ok = true;
            }
        }
        if (!ok)
            assert(!"throw");
    }
    for (int x = 12; x < n && x <= 111; x++) {
        int y = (x - 2) / 10 + 1;
        bool ok = false;
        for (int k = 0; !ok && k < K - 1; k++) {
            if (a[k][y + 1] == y + 1) {
                swap(a[k][y + 1], a[k][x + 1]);
                ok = true;
            }
        }
        if (!ok)
            assert(!"throw");
    }
    for (int x = 112; x < n && x <= 1111; x++) {
        int y = (x - 2) / 10 + 1;
        bool ok = false;
        for (int k = 0; !ok && k < K - 1; k++) {
            if (a[k][y + 1] == y + 1) {
                swap(a[k][y + 1], a[k][x + 1]);
                ok = true;
            }
        }
        if (!ok)
            assert(!"throw");
    }
}
bool readTest(){
    scanf("%d", &p[1]);
    if (p[1] == 0) return false;
    for (int i = 2; i <= n; i++)
        scanf("%d", &p[i]);
    return true;
}
void addAns(int id){
    ans[ansSz++] = id;
    for (int i = 1; i <= n; i++) {
        if (a[id][i] <= i) continue;
        swap(p[i], p[a[id][i]]);
    }
}
void moveToSecond(int q){
    while(q > 2) {
        int k = 0;
        while(k < K && a[k][q] >= q) k++;
        if (k == K)
            assert(!"throw");
        addAns(k);
        q = a[k][q];
    }
}
void mySwap(int pp, int qq){
    int qqq = p[qq];
    int oldAnsSz = ansSz;
    moveToSecond(pp);
    addAns(K - 1);
    qq = 1;
    while(p[qq] != qqq) qq++;
    moveToSecond(qq);
    int newAnsSz = ansSz;
    addAns(K - 1);
    for (int i = newAnsSz - 1; i >= oldAnsSz; i--)
        addAns(ans[i]);
}
void solve(){
    ansSz = 0;
    for (int X = 1; X <= n; X++) {
        int pos = 1;
        while(p[pos] != X) pos++;
        if (pos == X) continue;
        mySwap(X, pos);
    }
    printf("%d ", ansSz);
    for (int i = 0; i < ansSz; i++)
        printf("%d ", ans[i] + 1);
    printf("\n");
    fflush(stdout);
}
int main(){
    scanf("%d", &n);
    if (n == 1) {
        printf("0\n");
        fflush(stdout);
        while(true) {
            int x;
            scanf("%d", &x);
            if (x == 0) return 0;
            printf("0\n");
            fflush(stdout);
        }
    }
    precalc();
    printf("%d\n", K);
    for (int k = 0; k < K; k++) {
        for (int i = 1; i <= n; i++)
            printf("%d ", a[k][i]);
        printf("\n");
    }
    fflush(stdout);
    while(true) {
        if (!readTest()) break;
        solve();
    }
    return 0;
}



