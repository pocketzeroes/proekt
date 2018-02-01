#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int max(int a, int b){return a>b?a:b;}

int main() {
    int n;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; ++i){
        scanf("%d", &v[i]);
        --v[i];
    }
    int best = 0;
    for (int d = 0; d < n; ++d){
        int count = 0;
        for (int i = 0; i < n; ++i)
            if (v[(i + d) % n] == i)
                ++count;
        best = max(best, count);
    }
    printf("%d\n", best);
    return 0;
}
