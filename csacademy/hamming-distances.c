#pragma GCC optimize("Ofast")
#pragma GCC target("sse4,avx2")
#include <stdio.h>
#include <immintrin.h>

enum{ kNumBits = 8};
enum{ kMask    = (1 << kNumBits) - 1};
int cnt[1 << kNumBits][1 << kNumBits][kNumBits + 1];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int ans[17] = {0};
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        const int x_lower = x & kMask;
        const int x_upper = x >> kNumBits;
        for (int j = (1 << kNumBits) - 1; j >= 0; j -= 1){
            const int* ptr = cnt[x_lower][j];
            const int shift = _mm_popcnt_u32(j ^ x_upper);
            for (int k = 0; k <= kNumBits; k += 1) {
                ans[k + shift] += ptr[k];
            }
        }
        for (int j = (1 << kNumBits) - 1; j >= 0; j -= 1){
            cnt[j][x_upper][_mm_popcnt_u32(j ^ x_lower)] += 1;
        }
        for (int j = 0; j <= m; j += 1) {
            printf("%d%c", ans[j], " \n"[j == m]);
            ans[j] = 0;
        }
    }
    return 0;
}
