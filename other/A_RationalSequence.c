#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

#define MAX_INPUT 2147483647
char inbuf[256];


int GetSuccessor(int *pNum, int *pDenom, int prob_num){
    int level, num, denom;
    num = *pNum;
    denom = *pDenom;
    if(denom == 1) {
        *pNum = 1;
        *pDenom = num+1;
    } 
    else if(num < denom) {
        *pNum = denom;
        *pDenom = denom - num;
    } 
    else {
        level = num/denom;
        *pNum = denom;
        *pDenom = (2*level + 1)*denom - num;
    }
    return 0;
}
int main(){
    int nprob, curprob, index, num, denom, ret;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem %d data\n", curprob);
            return -3;
        }
        if(sscanf(&(inbuf[0]), "%d %d/%d", &index, &num, &denom) != 3){
            fprintf(stderr, "scan failed on problem header problem index %d\n", curprob);
            return -6;
        }
        if(index != curprob){
            fprintf(stderr, "problem index %d not = expected problem %d\n", index, curprob);
            return -7;
        }
        if((num < 1) || (num > MAX_INPUT)) {
            fprintf(stderr, "problem index %d numerator %d not in range 1-%d\n", curprob, num, MAX_INPUT);
            return -7;
        }
        if((denom < 1) || (denom > MAX_INPUT)) {
            fprintf(stderr, "problem index %d denominator %d not in range 1-%d\n", curprob, denom, MAX_INPUT);
            return -8;
        }
        ret = GetSuccessor(&num, &denom, curprob);
        if(ret < 0)
            return ret;
        printf("%d %d/%d\n", curprob, num, denom);
    }
    return 0;
}
