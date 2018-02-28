#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
#define mp newPair
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
typedef long long ll;
typedef pair pii;

enum{ INF = (int)2e7};
enum{ N   = 100100  };
int n;
pii a[N];
int b[N];

void read() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);
    qsort(b, m, sizeof(int), cmp);
    for (int i = 0; i < m; i++) {
        if (n == 0 || a[n - 1].first != b[i]) {
            a[n++] = mp(b[i], 0);
        }
        a[n - 1].second++;
    }
}
int solve() {
    int res = 0;
    if (n == 1) 
        return res;
    int Y = a[n - 1].second;
    int x = a[n - 2].first, y = 0;
    int pos = n - 2;
    while((pos >= 0 || y > 0) && x > 0) {
        if (pos >= 0 && x == a[pos].first) {
            y += a[pos].second;
            pos--;
        }
        y = max(0, y - Y);
        if (y >= Y) return INF;
        if (y == 0) {
            if (pos >= 0)
                x = a[pos].first;
            continue;
        }
        res += y;
        res = min(res, INF);
        y *= 2;
        x--;
    }
    if (y > 0) return INF;
    return res;
}
int main() {
    read();
    if (n == 1) {
        printf("0\n");
        return 0;
    }
    int ans = solve();
    int curAns = 0;
    if (n == 1) ans = 0;
    while(curAns < ans) {
        if (n <= 1)
            assert(!"throw");
        a[n - 1].first--;
        curAns += a[n - 1].second;
        a[n - 1].second *= 2;
        if (a[n - 1].first == a[n - 2].first) {
            n--;
            a[n - 1].second += a[n].second;
        }
        if (curAns >= ans) break;
        int val = curAns + solve();
        ans = min(ans, val);
    }
    printf("%d\n", ans);
    return 0;
}
