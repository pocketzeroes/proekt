#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef long long int64;
typedef int int32;
enum{ kInf  = 0x3f3f3f3f};
enum{ kMaxN = 105       };
int el[kMaxN][kMaxN];

int main() { 
    int n; 
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j +=1 ) {
            scanf("%d", &el[i][j]);
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            el[i][j] |= el[n - i - 1][n - j - 1];
            el[i][j] |= el[n - j - 1][i];
            el[i][j] |= el[j][n - i - 1];
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            printf("%d ", el[i][j] );
        }
        printf("\n");
    }
}
