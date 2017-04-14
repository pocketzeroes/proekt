#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


enum{ nmax = 1000010   };
enum{ mmax = 100100    };
enum{ mod  = 1000000007};

int n, m, len, x, y;
int father[20][nmax], size[20][nmax];

int root(int index, int x) {
    if (father[index][x] == x) {
        return x;
    }
    return father[index][x] = root(index, father[index][x]);
}

void unite(int index, int x, int y) {
    int rx = root(index, x);
    int ry = root(index, y);
    if (rx == ry) {
        return ;
    }
    if (size[index][rx] >= size[index][ry]) {
        size[index][rx] += size[index][ry];
        father[index][ry] = rx;
    } else {
        size[index][ry] += size[index][rx];
        father[index][rx] = ry;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < 20; ++ i) {
        for (int j = 1; j <= n - (1 << i) + 1; ++ j) {
            father[i][j] = j;
            size[i][j] = 1;
        }
    }
    for (int i = 1; i <= m; ++ i) {
        scanf("%d %d %d", &len, &x, &y);
        int k = 0;
        while ((1 << k) <= len) {
            k ++;
        }
        k --;
        unite(k, x, y);
        unite(k, x + len - (1 << k), y + len - (1 << k));
    }
    for (int k = 19; k >= 1; -- k) {
        for (int i = 1; i <= n - (1 << k) + 1; ++ i) {
            int r = root(k, i);
            unite(k - 1, i, r);
            unite(k - 1, i + (1 << (k - 1)), r + (1 << (k - 1)));
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++ i) {
        if (root(0, i) == i) {
            cnt ++;
        }
    }
    int ans = 1;
    for (int i = 1; i <= cnt; ++ i) {
        ans = (1LL * ans * 26) % mod;
    }
    printf("%d\n", ans);
}



















