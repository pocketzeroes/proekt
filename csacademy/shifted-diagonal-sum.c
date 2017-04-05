#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef long long int64;
enum { kMaxN   =(int) 1e3       };
enum { inf     =(int) 0x3f3f3f3f};
enum { kMaxVal =(int) 1e6       };
int element[kMaxN][kMaxN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            scanf("%d", &element[i][j]);
        }
    }
    int64 mx = - 1LL * inf * inf;
    for (int c = 0; c < n; c += 1) {
        int j = c;
        int64 sum = 0;
        for (int i = 0; i < n; i += 1, j += 1, j %= n) {
            sum += element[i][j];           
        }
        if (sum > mx) {
            mx = sum;
        }
    }
    printf("%lld", mx);
    return 0;
}
