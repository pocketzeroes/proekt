#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>

inline int64_t min(int64_t a,int64_t b){return a<b?a:b;}
inline int64_t max(int64_t a,int64_t b){return a>b?a:b;}

enum{ MAX_N = (int)1e5};
int n;
int x[MAX_N];
long long minVal[MAX_N], maxVal[MAX_N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &minVal[i] , &maxVal[i]);
    }
    long long s = 0;
    for (int i = 1; i < n; ++i) {
        s *= -1;
        s += x[i] - x[i - 1];
        if (i % 2) {
            minVal[0] = max(minVal[0], s - maxVal[i]);
            maxVal[0] = min(maxVal[0], s - minVal[i]);
        } 
        else {
            minVal[0] = max(minVal[0], minVal[i] - s);
            maxVal[0] = min(maxVal[0], maxVal[i] - s);
        }
    }
    printf("%lld", max(0LL, maxVal[0] - minVal[0] + 1));
}

