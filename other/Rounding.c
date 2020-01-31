#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char str  [50001];
char*names[50001];
int  d    [50001];

int validate(int x){
    if (x > 49) return 49;
    if (x <-50) return-50;
    return x;
}
int main(){
    int n;
    int sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%s%d", str, &d[i]);
        d[i] *= 100;
        sum += d[i];
        names[i] = strdup(str);
    }
    int l = 10000 - sum - 49 * (n - 1);
    int r = 10000 - sum + 50 * (n - 1);
    if (r > 49) r = 49;
    if (l <-50) l =-50;
    if (l <= r){
        for (int i = 0; i < n; ++i) {
            printf("%s %.2f %.2f\n", names[i], fmax(0, d[i] + l) / 100.0, fmin(10000, d[i] + r) / 100.0);
        }
    }
    else
        printf("IMPOSSIBLE\n");
    return 0;
}
