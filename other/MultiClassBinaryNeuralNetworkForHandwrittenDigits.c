#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    for(int i=0; i<150; i++){
        for(int j=0; j<51; j++){
            int r = rand()%3-1;
            printf("%d ", r);
        }
        puts("");
    }
    return 0;
}
