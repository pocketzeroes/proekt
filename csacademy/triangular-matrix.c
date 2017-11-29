#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ kMaxN = 3005};
bool color[kMaxN];
char row[kMaxN + 1];

int main() {
    int n;
    scanf("%d", &n);
    color[0] = true;
    for (int i = 0; i < n; i += 1) {
        scanf("%s", &row);
        for (int j = i; j >= 1; j -= 1) {
            color[j] |= color[j - 1];
        }
        char best = -1;
        for (int j = 0; j <= i; j += 1) {
            if (color[j] && (best == -1 || best > row[j])) {
                best = row[j];
            }
        }
        for (int j = 0; j <= i; j += 1) {
            color[j] &= (best == row[j]);
        }
        printf("%c", best);
    }
    puts("");
}
