#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int pow3[20];

int main(){
    pow3[0]=1;
    for(int i = 1; i < 20; ++i){
        pow3[i] = pow3[i - 1] * 3;
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        int digits[20];
        for(int j = 0; j < 20; ++j){
            digits[j] = (x + 1) % 3 - 1;
            x = (x + 1) / 3;
        }
        if (i)
            puts("");
        printf("left pan:");
        for (int j = 19; j >= 0; --j)
            if (digits[j] == -1)
                printf(" %d", pow3[j]);
        puts("");
        printf("right pan:");
        for (int j = 19; j >= 0; --j)
            if(digits[j] == 1)
                printf(" %d", pow3[j]);
        puts("");
    }
    return 0;
}
