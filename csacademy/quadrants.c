#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cnt[4];
int main(){
    int n, x, y;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d", &x, &y);
        if (x > 0 && y > 0) cnt[0]++;
        if (x < 0 && y > 0) cnt[1]++;
        if (x < 0 && y < 0) cnt[2]++;
        if (x > 0 && y < 0) cnt[3]++;
    }
    printf("%d\n", (cnt[0] > 0) + (cnt[1] > 0) + (cnt[2] > 0) + (cnt[3] > 0));
    return 0;
}
