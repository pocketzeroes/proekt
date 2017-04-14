#include <stdio.h>

enum{ kMaxVal      =(int) 1e6};
enum{ kMaxBit      = 20     };
enum{ kMaxN        =(int)1e5};
enum{ kUnavailable = (1 << (kMaxBit + 1)) - 1};
int dp[kMaxVal + 1];

int main() {
    for (int i = 0; i <= kMaxVal; i++)
        dp[i] = kUnavailable;
    int n; 
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        int x; 
        scanf("%d", &x);
        dp[x] = x;
    }
    int answer = 1;
    for (int i = kMaxVal; i > 0; i--){
        if (dp[i] == i) 
            answer++;
        for (int j = 0; j < kMaxBit; j++){
            if ((1 << j) & i) 
                dp[i ^ (1 << j)] &= dp[i];
        }
    }
    printf("%d\n", answer );
    return 0;
}
