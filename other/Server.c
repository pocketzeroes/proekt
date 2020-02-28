#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, time;
    scanf("%d %d", &n, &time);
    int i;
    int total=0;
    for(i=0; i<n; i++){
        int temp;
        scanf("%d", &temp);
        total+=temp;
        if(total>time)
            break;
    }
    printf("%d\n", i);
    return 0;
}
