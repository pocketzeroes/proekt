#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum{ cardMax = 1001};

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int freq[cardMax];
    memset(freq,0,sizeof(freq));
    for (int i = 0; i < n; ++i) {
        int x; 
        scanf("%d", &x);
        freq[x]++;
    }
    int sol = 0;
    for (int i = 1; i < cardMax; ++i) {
        freq[i] += freq[i - 1];
        if (i >= k && freq[i] - freq[i - k] + m >= k) {
            ++sol;
        }
    }
    printf("%d\n",  sol);
    return 0;
}
