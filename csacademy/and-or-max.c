#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
enum{ B = 128};

void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    int a[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    int M = (N + B - 1) / B;
    int AND[M]; fill(AND, M, -1);
    int OR [M]; memset(OR, 0, sizeof(OR));
    int ma [M]; fill(ma , M, -1);
    while (Q--){
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r), l--;
        if (t == 1 || t == 2) {
            int x; scanf("%d", &x);
            for (int i = l; i < r;) {
                if (i % B == 0 && i + B <= r) {
                    int j = i / B;
                    int prev = ~AND[j] | OR[j];
                    if (t == 1) AND[j] &= x, OR[j] &= x;
                    if (t == 2) AND[j] |= x, OR[j] |= x;
                    int cur = ~AND[j] | OR[j];
                    if (cur != prev) ma[j] = -1;
                    i += B;
                }
                else {
                    int j = i / B;
                    if (AND[j] != -1 || OR[j] != 0) {
                        for (int i = j * B; i < (j + 1) * B; i++)
                            a[i] = a[i] & AND[j] | OR[j];
                        AND[j] = -1, OR[j] = 0;
                    }
                    if (t == 1) a[i] &= x;
                    if (t == 2) a[i] |= x;
                    ma[j] = -1;
                    i++;
                }
            }
        }
        if (t == 3) {
            int ans = 0;
            for (int i = l; i < r;) {
                if (i % B == 0 && i + B <= r) {
                    int j = i / B;
                    if (ma[j] == -1) {
                        ma[j] = 0;
                        int cur = ~AND[j] | OR[j];
                        for (int i = j * B; i < (j + 1) * B; i++)
                            ma[j] = max(ma[j], a[i] & ~cur);
                    }
                    ans = max(ans, ma[j] & AND[j] | OR[j]);
                    i += B;
                }
                else {
                    int j = i / B;
                    if (AND[j] != -1 || OR[j] != 0) {
                        for (int i = j * B; i < (j + 1) * B; i++)
                            a[i] = a[i] & AND[j] | OR[j];
                        AND[j] = -1, OR[j] = 0, ma[j] = -1;
                    }
                    ans = max(ans, a[i]);
                    i++;
                }
            }
            printf("%d\n", ans);
        }
    }
}
