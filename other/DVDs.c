#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int k;
    scanf("%d", &k);
    for(int i=0; i<k; i++){
        long n;
        scanf("%ld", &n);
        long temp = 1;
        for(long j = 0; j < n; j++){
            long temp2;
            scanf("%ld", &temp2);
            if (temp2 == temp)
                temp++;
        }
        printf("%d\n", n-temp+1);
    }
    return 0;
}
