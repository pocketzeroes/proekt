#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ kMaxN =(int) 1e5+5}; 
enum{ inf   =(int) 1e9+6};

int el[kMaxN];

int main() {
    int n, x; 
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i += 1) {
        scanf("%d", &el[i]);
    }
    el[n + 1] = inf;
    for (int i = 1; i <= n + 1; i += 1) {
        if (el[i] > x) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
