#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int N;
    scanf("%d", &N);
    int L = 1;
    int R = N;
    while (L < R){
        int mid = (L + R) / 2;
        printf("? %d\n", mid); fflush(stdout);
        int fb;
        scanf("%d", &fb);
        if (fb == 0){
            L = R = mid;
            break;
        }
        else if (fb < 0){
            L = mid + 1;
        }
        else{
            R = mid - 1;
        }
    }
    printf("= %d\n", L);
    return 0;
}
