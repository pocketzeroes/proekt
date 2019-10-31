#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXP = 10000};
int  profs   [MAXP];
long opusNums[MAXP];
int  nprofs;

int main(){
    scanf("%d", &nprofs);
    for(int i=0; i<nprofs; i++){
        scanf("%ld", &opusNums[i]);
        profs[i] = i+1;
    }
    int curr = 0;
    while(nprofs > 1){
        int nextOut = (curr + opusNums[curr] - 1)%nprofs;
        for(int i=nextOut+1; i<nprofs; i++){
            opusNums[i-1] = opusNums[i];
            profs   [i-1] = profs[i];
        }
        nprofs--;
        curr = nextOut%nprofs;
    }
    printf("%d\n", profs[0]);
    return 0;
}
