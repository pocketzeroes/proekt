#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_PROB    1000
#define MAX_N      10000
#define MAX_M        100
typedef unsigned long  u64;
typedef unsigned short u16;
char inbuf[256];
u64 oneCount[2][MAX_N];

u64 FindMPartions(int n, int m, int level, u64 *chk1, u64 *chk2){
    u64 total, i, j, n1, rem, rem1, subcnt, check1, check2;
    u64 *pNew, *pPrev;
    if(n < m) {
        memset(&(oneCount[level & 1][0]), 0, MAX_N*sizeof(u64));
        oneCount[level & 1][n] = 1;
        *chk1 = *chk2 = 1;
        return 1;
    }
    n1     = n/m;
    rem    = n % m;
    rem1   = n1 % m;
    subcnt = FindMPartions(n1, m, level+1, &check1, &check2);
    check2 = (check2 * (1+rem1)) % m;
    total  = subcnt;
    memset(&(oneCount[level & 1][0]), 0, MAX_N*sizeof(u16));
    pNew  = &(oneCount[level & 1][0]);
    pPrev = &(oneCount[(level+1) & 1][0]);
    pNew[rem] = subcnt;     
    for(i = 1; i <= n1 ; i++) {
        total = (total + i*pPrev[i]); 
        check1 = (check1 + i*pPrev[i]) % m;
        if(pPrev[i] > 0) {
            for(j = 1; j <= i ; j++)
                pNew[j*m+rem] += pPrev[i];
        }
    }
    *chk1 = check1;
    *chk2 = check2;
    if(check1 != check2) {
        printf("Chk1 %u chk2 %u n %d m %d\n", check1, check2, n, m);
    }
    return total;
}
int main(){
    int nprob, curprob, index;
    int m, n;
    u64 result, check1, check2;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    if((nprob < 5) || (nprob > MAX_PROB)){
        fprintf(stderr, "problem count %d not in range 5 .. %d\n", nprob, MAX_PROB);
        return -20;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem %d header\n", curprob);
            return -3;
        }
        if(sscanf(&(inbuf[0]), "%d %d %d", &index, &m, &n) != 3){
            fprintf(stderr, "scan failed on problem %d dat\n", curprob);
            return -4;
        }
        if(index != curprob){
            fprintf(stderr, "problem index %d not = expected problem %d\n", index, curprob);
            return -5;
        }
        if((m < 3) || (m > MAX_M) || (n < 2) || (n > MAX_N)){
            fprintf(stderr, "problem %d: m %d out of rande [2, %d] or n %d out of range [2, %d]\n", index, m, MAX_M, n, MAX_N);
            return -6;
        }
        result = FindMPartions(n, m, 0, &check1, &check2);
        printf("%d %u\n", curprob, result);
    }
    return 0;
}
