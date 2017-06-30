#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef struct NodeS {
    int l, r;
}Node;
Node node[131072];
void linkNode(int l, int r) {
    node[r].l = l, node[l].r = r;
}
int main() {
    int i, p;
    int n, m, cases = 0;
    while (scanf("%d %d", &n, &m) == 2) {
        for( i = 1; i <= n; i++)
            node[i].l = i - 1, node[i].r = i + 1;
        node[0].r = 1, node[0].l = n, node[n].r = 0;
        int cmd, X, Y;
        int rflag = 0;
        while (m--) {
            scanf("%d", &cmd);
            if (cmd == 4) {
                rflag = !rflag;
                continue;
            }
            scanf("%d %d", &X, &Y);
            if(cmd == 3) { 
                if (node[Y].r == X)
                    swap(X, Y);
                if (Y == node[X].r) { 
                    linkNode(node[X].l, Y), linkNode(X, node[Y].r);
                    linkNode(Y, X);
                } 
                else {
                    int Yl = node[Y].l, Yr = node[Y].r;
                    linkNode(node[X].l, Y), linkNode(Y, node[X].r);
                    linkNode(Yl, X), linkNode(X, Yr);
                }
            } 
            else {
                if (rflag)
                    cmd = 3 - cmd;
                if ((cmd == 1 && node[Y].l == X) || (cmd == 2 && node[Y].r == X))
                    continue;
                if (cmd == 1) { 
                    linkNode(node[X].l, node[X].r);
                    linkNode(node[Y].l, X), linkNode(X, Y);
                } 
                else { 
                    linkNode(node[X].l, node[X].r);
                    linkNode(X, node[Y].r), linkNode(Y, X);
                }
            }
        }
        long long ret = 0;
        for( i = 1, p = 0; i <= n; i++) {
            p = node[p].r;
            if (i&1)
                ret += p;
        }
        if (rflag && n%2 == 0) {
            ret = (long long)(n) * (n + 1)/2 - ret;
        }
        printf("Case %d: %lld\n", ++cases, ret);
    }
    return 0;
}






















































