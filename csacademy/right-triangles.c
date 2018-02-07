#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define pb push_back
#define mp make_pair
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long ll;

enum{ N  = 100000};
enum{ MX = 100000};
int n;
int x[N], y[N];
int ord[N], ans[N], fen[MX + 1];

int cmp(const void*pa, const void*pb){
    int*lhs=(int*)pa;
    int*rhs=(int*)pb;
    return( (ll)x[*lhs] * y[*rhs] > (ll)x[*rhs] * y[*lhs])?-1:1;
}
void fenInc(int ind) {
    for (; ind <= MX; ind |= ind + 1) {
        ++fen[ind];
    }
}
int fenGet(int ind) {
    int res = 0;
    for (; ind >= 0; ind = (ind & (ind + 1)) - 1) {
        res += fen[ind];
    }
    return res;
}
int main() {
    scanf("%d", &n);
    forn(i, n) scanf("%d%d", x + i, y + i);
    forn(i, n) ord[i] = i;
    qsort(ord, n, sizeof(int), cmp);
    forn(ii, n) {
        int i = ord[ii];
        ans[i] = fenGet(x[i]);
        fenInc(x[i]);
    }
    forn(i, n) printf("%d ", ans[i]);
    puts("");
    return 0;
}
