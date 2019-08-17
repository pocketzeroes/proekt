#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXN = 1005};

int TC = 1, T, R, K, N, group [MAXN];
ll euros [MAXN], seen [MAXN];

int main(){
    for (scanf ("%d", &T); TC <= T; TC++){
        scanf ("%d %d %d", &R, &K, &N);
        for (int i = 0; i < N; i++)
            scanf ("%d", group + i);
        memset (seen, -1, sizeof (seen));
        ll total = 0;
        bool jump = false;
        for (int r = 0, i = 0; r < R; r++){
            if (!jump && seen [i] != -1){
                jump = true;
                total += (ll) (R - r) / (r - seen [i]) * (total - euros [seen [i]]);
                r += (ll) (R - r) / (r - seen [i]) * (r - seen [i]) - 1;
                continue;
            }
            if (!jump){
                seen [i] = r;
                euros [r] = total;
            }
            int it = 0, people = 0;
            while (it < N && people + group [i] <= K){
                people += group [i];
                i = (i + 1) % N;
                it++;
            }
            total += people;
        }
        printf ("Case #%d: %lld\n", TC, total);
    }
    return 0;
}
