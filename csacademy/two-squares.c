#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int R, C, k;

int main(){
    scanf("%d %d %d", &R, &C, &k);
    int v[R+1][C+1];
    int sum(int r1, int c1, int r2, int c2){
        return v[r2][c2] - v[r1 - 1][c2] - v[r2][c1 - 1] + v[r1 - 1][c1 - 1];
    }
    int z = 0;
    for (int i = 1; i <= R; ++i)
        for (int j = 1; j <= C; ++j) {
            scanf("%d", &v[i][j]);
            z += !v[i][j];
            v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1];
        }
    int res = 0;
    for (int r1 = 1; r1 + k - 1 <= R; ++r1)
        for (int r2 = r1; r2 + k - 1 <= R && r1 + k - 1 >= r2; ++r2) {
            for (int o = 0; o < k; ++o) {
                for (int c = 1; c + o + k - 1 <= C; ++c) {
                    int cur = sum(r1, c, r1 + k - 1, c + k - 1);
                    cur += sum(r2, c + o, r2 + k - 1, c + o + k - 1);
                    cur -= sum(r2, c + o, r1 + k - 1, c + k - 1);
                    if (res < cur)
                        res = cur;
                    cur = sum(r2, c, r2 + k - 1, c + k - 1);
                    cur += sum(r1, c + o, r1 + k - 1, c + o + k - 1);
                    cur -= sum(r2, c + o, r1 + k - 1, c + k - 1);
                    if (res < cur)
                        res = cur;
                }
            }
        }
    int mxC[C + 1]; memset(mxC, 0, sizeof(mxC));
    for (int c = k; c <= C; ++c) {
#define mx mxC[c]
        for (int r = 1; r + k - 1 <= R; ++r)
            mx = max(mx, sum(r, c - k + 1, r + k - 1, c));
        mxC[c] = max(mxC[c], mxC[c - 1]);
    }
    #undef mx
    for (int c = C - k + 1; c > 0; --c) {
        int mx = 0;
        for (int r = 1; r + k - 1 <= R; ++r)
            mx = max(mx, sum(r, c, r + k - 1, c + k - 1));
        res = max(res, mx + mxC[c - 1]);
    }
    int mxR[R + 1]; memset(mxR, 0, sizeof(mxR));
    
    for (int r = k; r <= R; ++r) {
#define mx mxR[r]
        for (int c = 1; c + k - 1 <= C; ++c)
            mx = max(mx, sum(r - k + 1, c, r, c + k - 1));
        mxR[r] = max(mxR[r], mxR[r - 1]);
    }
    #undef mx
    for (int r = R - k + 1; r>0; --r) {
        int mx = 0;
        for (int c = 1; c + k - 1 <= C; ++c)
            mx = max(mx, sum(r, c, r + k - 1, c + k - 1));
        res = max(res, mx + mxR[r - 1]);
    }
    printf("%d\n", res + z);
    return 0;
}
