#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef unsigned long DWORD;
#define MAX_ORDER   10000
char inbuf[256];

int primes[MAX_ORDER+1];
int phi[MAX_ORDER+1];
int fareyCnt[MAX_ORDER+1];
int lastFarey = 0;
int primeFacts[20];
int factCnts[20];

void MakePrimes(void){
    int i, j;
    for(i = 0; i <=  MAX_ORDER ; i++) {
        primes[i] = 1;
        fareyCnt[i] = 0;
    }
    for(i = 2; i <= MAX_ORDER ; i++) {
        if(primes[i] == 1) {
            for(j = i*2; j <= MAX_ORDER ; j += i) {
                if(primes[j] == 1) primes[j] = i;
            }
        }
    }
    fareyCnt[1] = 2;
    lastFarey = 1;
}

int GetPhi(val){
    int notfound, i, result, cur, lastfact = 0;
    if(primes[val] == 1) 
        return (val - 1);
    while(val > 1) {
        cur = primes[val];
        if(cur == 1) 
           cur = val;
        for(notfound = 1, i = 0; i < lastfact && notfound ; i++) {
            if(cur == primeFacts[i]) {
                notfound = 0;
                factCnts[i]++;
                break;
            }
        }
        if(notfound) {
            primeFacts[lastfact] = cur;
            factCnts[lastfact] = 1;
            lastfact++;
        }
        val = val/cur;
    }
    result = 1;
    for(i = 0; i < lastfact ; i++) {
        for(cur = 1; cur < factCnts[i]; cur++) {
            result *= primeFacts[i];
        }
        result *= (primeFacts[i] - 1);
    }
    return result;
}
int fareysum(int order, int *pnum, int *pdenom){
    int j;
    if(order <= lastFarey)
        return fareyCnt[order];
    for(j = lastFarey; j < order; j++)
        fareyCnt[j+1] = fareyCnt[j] + GetPhi(j+1);
    lastFarey = order;
    j = 3*fareyCnt[order] - 4;
    if((j & 1) == 0) {
        *pnum = j/2;
        *pdenom = 1;
    }
    else {
        *pnum = j;
        *pdenom = 2;
    }
    return 0;
}
int main(){
    int nprob, curprob, index, order, num, denom;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    MakePrimes();
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem %d header\n", curprob);
            return -3;
        }
        if(sscanf(&(inbuf[0]), "%d %d", &index, &order) != 2){
            fprintf(stderr, "scan failed on problem header problem index %d\n", curprob);
            return -6;
        }
        if(index != curprob){
            fprintf(stderr, "problem index %d not = expected problem %d\n", index, curprob);
            return -7;
        }
        if((order < 1) || (order > MAX_ORDER)){
            fprintf(stderr, "problem index %d order %d not in range 1-%d\n", curprob, order, MAX_ORDER);
            return -8;
        }
        fareysum(order, &num, &denom);
        if(denom == 1) {
            printf("%d %d\n", index, num);
        }
        else {
            printf("%d %d/%d\n", index, num,denom);
        }
    }
    return 0;
}
