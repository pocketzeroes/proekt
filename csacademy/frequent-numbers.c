#include <stdio.h>
int freq[1001];

int main() {
    int n, k; 
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++){
        int x; 
        scanf("%d", &x);
        freq[x]++;
    }
    int ans = 0;
    for (int i = 1; i <= 1000; i++){
        ans += (freq[i] >= k);
    }
    printf("%d", ans);
    return 0;
}
