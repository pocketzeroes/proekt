#include <stdio.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

#define kMaxN 100001
int where[kMaxN];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        int p;
        scanf("%d", &p);
        where[p] = i;
    }
    int mn_pos = n + 1;
    int mx_distance = -1;
    for (int i = 1; i <= n; i += 1) {
        mx_distance = max(mx_distance, where[i] - mn_pos);
        mn_pos = min(mn_pos, where[i]);
    }
    printf("%d", mx_distance);
    return 0;
}
