#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAGIC_MODULUS   (1001113)

typedef unsigned long u64;

#define MAX_ORDER   100
#define NOT_YET_SET (0xffffffff)
char inbuf[256];

u64 descnts[MAX_ORDER+1][MAX_ORDER];

void InitDescnt(void){
    int i, j;
    for(i = 0; i <= MAX_ORDER ; i++) 
        for(j = 0; j < MAX_ORDER ; j++) 
            descnts[i][j] = NOT_YET_SET;
    for(i = 1; i <= MAX_ORDER ; i++) {
        descnts[i][0  ] = 1;
        descnts[i][i-1] = 1;
    }
}
u64 descent(int order, int count){
    if((count == 0) || (count == (order -1))) {
        return 1;
    }
    if(descnts[order][count] != NOT_YET_SET) {
        return descnts[order][count];
    }
    descnts[order][count] = (((count + 1)) * descent(order-1, count) + ((order - count)) * descent(order-1, count-1)) % MAGIC_MODULUS;
    return descnts[order][count];
}
int main(){
    int nprob, curprob, index, order, count;
    u64 dcount;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL)  {
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)  {
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    InitDescnt();
    for(curprob = 1; curprob <= nprob ; curprob++)  {
        if(fgets(&(inbuf[0]), 255, stdin) == NULL)  {
            fprintf(stderr, "Read failed on problem %d header\n", curprob);
            return -3;
        }
        if(sscanf(&(inbuf[0]), "%d %d %d", &index, &order, &count) != 3)    {
            fprintf(stderr, "scan failed on problem header problem index %d\n",
                curprob);
            return -6;
        }
        if(index != curprob)    {
            fprintf(stderr, "problem index %d not = expected problem %d\n",
                index, curprob);
            return -7;
        }
        if((order < 1) || (order > MAX_ORDER)) {
            fprintf(stderr, "problem index %d order %d not in range 1-%d\n",
                curprob, order, MAX_ORDER);
            return -8;
        }
        if((count < 0) || (count > (order - 1))) {
            fprintf(stderr, "problem index %d count %d not in range 0-%d\n",
                curprob, count, order-1);
            return -8;
        }
        dcount = descent(order, count);
        printf("%d %llu\n", index, dcount);
    }
    return 0;
}

