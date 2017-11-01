#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n, r, k, b;
    scanf("%d %d %d", &n, &r, &k);
    b = n - r;
    int rr = r, bb = b, kk = k;
    int mx = 0;
    int maxed = false;
    for (int i = 0; i < kk; ++i) {
        if (rr == n) maxed = true;
        if (maxed) { --rr; ++ bb; }
        else {++rr; --bb;};
    }
    mx = rr;
    maxed = false;
    int mn = 0;
    rr = r, bb = b;
    for (int i = 0; i < kk; ++i) {
        if (bb == n) maxed = true;
        if (maxed) { ++ rr; -- bb; }
        else { -- rr; ++ bb; }
    }
    mn = rr;
    printf("%d %d\n", mn, mx);
}
