#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include <ctype.h>

enum{ SIZE = 1 << 17};
char buffer[SIZE];
int pointer = SIZE;
enum{ MAXN     = 100000    };
enum{ MOD      = 1000000007};
enum{ MAXNODES = 262144    };
int v[1 + MAXN], bigStack[1 + MAXN], smallStack[1 + MAXN];
int tree[1 + MAXNODES], lazy[1 + MAXNODES];
int from, to, where, change;

char Advance() {
    if (pointer == SIZE) {
        fread(buffer, 1, SIZE, stdin);
        pointer = 0;
    }
    return buffer[pointer++];
}
int Read() {
    int answer = 0;
    char ch = Advance();
    while (!isdigit(ch))
        ch = Advance();
    while (isdigit(ch)) {
        answer = answer * 10 + ch - '0';
        ch = Advance();
    }
    return answer;
}
int RaiseToPower(int base, int power) {
    int answer = 1;
    while (power) {
        if (power % 2)
            answer = (1LL * answer * base) % MOD;
        base = (1LL * base * base) % MOD;
        power /= 2;
    }
    return answer;
}
void Update(int node, int left, int right) {
    if (from <= left && right <= to) {
        lazy[node] = (1LL * lazy[node] * change) % MOD;
        return;
    }
    lazy[2 * node] = (1LL * lazy[2 * node] * lazy[node]) % MOD;
    lazy[2 * node + 1] = (1LL * lazy[2 * node + 1] * lazy[node]) % MOD;
    lazy[node] = 1;
    int middle = (left + right) / 2;
    if (from <= middle)
        Update(2 * node, left, middle);
    if (middle + 1 <= to)
        Update(2 * node + 1, middle + 1, right);
    tree[node] = (1LL * tree[2 * node] * lazy[2 * node] + 1LL * tree[2 * node + 1] * lazy[2 * node + 1]) % MOD;
}
void Set(int node, int left, int right) {
    if (left == right) {
        tree[node] = change;
        return;
    }
    lazy[2 * node] = (1LL * lazy[2 * node] * lazy[node]) % MOD;
    lazy[2 * node + 1] = (1LL * lazy[2 * node + 1] * lazy[node]) % MOD;
    lazy[node] = 1;
    int middle = (left + right) / 2;
    if (where <= middle)
        Set(2 * node, left, middle);
    else
        Set(2 * node + 1, middle + 1, right);
    tree[node] = (1LL * tree[2 * node] * lazy[2 * node] + 1LL * tree[2 * node + 1] * lazy[2 * node + 1]) % MOD;
}
int main() {
    int n, bigTop = 0, smallTop = 0;
    scanf("%d", &n);
    for (int i = 1; i <= MAXNODES; i++)
        lazy[i] = 1;
    int divideBy2 = RaiseToPower(2, MOD - 2), answer = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        while (smallTop && v[i] <= v[smallStack[smallTop]]) {
            if (v[i] != v[smallStack[smallTop]]) {
                from = smallStack[smallTop - 1] + 1;
                to = smallStack[smallTop];
                change = (1LL * v[i] * RaiseToPower(v[smallStack[smallTop]], MOD - 2)) % MOD;
                Update(1, 1, n);
            }
            smallTop--;
        }
        smallTop++;
        smallStack[smallTop] = i;
        while (bigTop && v[i] >= v[bigStack[bigTop]]) {
            if (v[i] != v[bigStack[bigTop]]) {
                from = bigStack[bigTop - 1] + 1;
                to = bigStack[bigTop];
                change = (1LL * v[i] * RaiseToPower(v[bigStack[bigTop]], MOD - 2)) % MOD;
                Update(1, 1, n);
            }
            bigTop--;
        }
        bigTop++;
        bigStack[bigTop] = i;
        where = i;
        change = (1LL * v[i] * v[i]) % MOD;
        if (i != 1)
            change = (1LL * change * RaiseToPower(2, i - 2)) % MOD;
        if (i != n)
            change = (1LL * change * RaiseToPower(2, n - i - 1)) % MOD;
        Set(1, 1, n);
        if (i != n && i != 1) {
            from = 1;
            to = i - 1;
            change = divideBy2;
            Update(1, 1, n);
        }
        answer = (1LL * tree[1] * lazy[1] + answer) % MOD;
    }
    printf("%d\n", answer);
    return 0;
}




















































