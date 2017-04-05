#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

enum{ kMaxN = 101};
int points[kMaxN];

int main() {
    int n; 
    scanf("%d", &n);
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            int winner; 
            scanf("%d", &winner);
            if (winner == 0)
                continue;
            if (winner == 1)
                points[i] += 1;
            else
                points[j] += 1;
        }
    }
    int mx_points     = -1;
    int winner_number = 0;
    for (int i = 1; i <= n; i += 1) {
        if (mx_points < points[i]) {
            mx_points = points[i];
            winner_number = i;
        }
    }
    printf("%d", winner_number);
    return 0;
}
