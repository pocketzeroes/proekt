#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool notprime[40000];

int main(){
    notprime[0] = true;
    notprime[1] = true;
    for (int i = 2; i < 20000; ++i) {
        if (notprime[i]) 
            continue;
        for (int j = 2; i * j < 40000; ++j) {
            notprime[i * j] = true;
        }
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        int x;
        scanf("%d", &x);
        int tot = 0;
        for (int j = 2; j * 2 <= x; ++j)
            if (!notprime[j] && !notprime[x - j])
                tot++;
        printf("%d has %d representation(s)\n", x, tot);
        for (int j = 2; j * 2 <= x; ++j)
            if (!notprime[j] && !notprime[x - j])
                printf("%d+%d\n", j, x - j);
        puts("");
    }
    return 0;
}
