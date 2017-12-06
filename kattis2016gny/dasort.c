#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef unsigned long DWORD;

#define MAX_PROBS   1000
#define MAX_VALS    1000
#define VAL_LIMIT   1000000000

typedef struct _dasort_{
    DWORD val;
    DWORD loc;
    struct _dasort_ *pNext;
} DASORT, *PDASORT;
typedef struct _rsort_{
    PDASORT pHead;
    PDASORT pTail;
} RSORT;

DWORD prevmin, minval;
int minloc, aftermincnt;

#define RSHIFT  10      
#define RSIZE   1024    
#define RMASK   0x3ff   

DASORT values[MAX_VALS+1];
RSORT sorts[2][RSIZE];
char inbuf[256];

void ClearRSort(int index){
    int i;
    for(i = 0; i < RSIZE ; i++) {
        sorts[index][i].pHead = sorts[index][i].pTail = NULL;
    }
}
void RSortInsert(PDASORT pdas, DWORD val, int index){
    val &= RMASK;
    if(sorts[index][val].pHead == NULL) {
        sorts[index][val].pHead = sorts[index][val].pTail = pdas;
        pdas->pNext = NULL;
    }
    else {
        sorts[index][val].pTail->pNext = pdas;
        pdas->pNext = NULL;
        sorts[index][val].pTail = pdas;
    }
}
int main(){
    int nprob, curprob, index, nvals, count;
    int rem, cursz, i, j, curstart;
    DWORD vals[10], ind, prevloc, firstMoved;
    PDASORT pdas, nxtpdas;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    if(nprob > MAX_PROBS){
        fprintf(stderr, "Problem count %d > Max allowed %d\n", nprob, MAX_PROBS);
        return -3;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem %d header\n", curprob);
            return -4;
        }
        if(sscanf(&(inbuf[0]), "%d %d", &index, &nvals) != 2){
            fprintf(stderr, "scan failed on problem %d header\n", curprob);
            return -5;
        }
        if(index != curprob){
            fprintf(stderr, "problem index %d not = expected problem %d\n",
                index, curprob);
            return -6;
        }
        if(nvals > MAX_VALS){
            fprintf(stderr, "Problem %d val count %d > Max allowed %d\n", curprob, nvals, MAX_VALS);
            return -7;
        }
        rem = nvals; i= 0;
        curstart = 1;
        prevmin = minval = VAL_LIMIT + 1;
        minloc = -1;
        aftermincnt = 0;
        while(rem > 0){
            i++;
            cursz = rem;
            if(cursz > 10){
                cursz = 10;
            } 
            rem -= cursz;
            if(fgets(&(inbuf[0]), 255, stdin) == NULL){
                fprintf(stderr, "Read failed on problem %d data line %d\n", curprob, i);
                return -8;
            }
            if(sscanf(&(inbuf[0]), "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu ",
                &(vals[0]), &(vals[1]), &(vals[2]), &(vals[3]), &(vals[4]), 
                &(vals[5]), &(vals[6]), &(vals[7]), &(vals[8]), &(vals[9])) != cursz){
                fprintf(stderr, "scan failed on problem %d data line %d\n", curprob, i);
                return -9;
            }
            for(j = 0; j < cursz; j++) {
                if(vals[j] > VAL_LIMIT) {
                    fprintf(stderr, "problem %d value %d = %lu too large\n", curprob, 10*(i-1)+j, vals[j]);
                    return -10;
                }
                values[curstart + j].val = vals[j];
                values[curstart + j].loc = curstart+j;
                if(vals[j] < minval) {
                    prevmin = minval;
                    minval = vals[j];
                    minloc = curstart+j;
                    aftermincnt = 0;
                }
                else if(vals[j] <= prevmin) {
                    aftermincnt++;
                }
            }
            curstart += cursz;
        }
        ClearRSort(0);
        pdas = &(values[minloc]);
        for(i = minloc; i <= nvals ; i++, pdas++) {
            if(pdas->val <= prevmin) {
                ind = pdas->val & RMASK;
                RSortInsert(pdas, ind, 0);
            }
        }
        ClearRSort(1);
        for(i = 0; i < RSIZE; i++) {
            pdas = sorts[0][i].pHead;
            while(pdas != NULL) {
                nxtpdas = pdas->pNext;
                ind = (pdas->val >> RSHIFT) & RMASK;
                RSortInsert(pdas, ind, 1);
                pdas = nxtpdas;
            }
        }
        ClearRSort(0);
        for(i = 0; i < RSIZE; i++) {
            pdas = sorts[1][i].pHead;
            while(pdas != NULL) {
                nxtpdas = pdas->pNext;
                ind = (pdas->val >> (2*RSHIFT)) & RMASK;
                RSortInsert(pdas, ind, 0);
                pdas = nxtpdas;
            }
        }
        count = prevloc = 0;
        firstMoved = VAL_LIMIT + 1;
        for(i = 0; (i < RSIZE) && (prevloc < MAX_VALS) ; i++) {
            pdas = sorts[0][i].pHead;
            while(pdas != NULL) {
                if((pdas->loc >= prevloc) && (pdas->val <= firstMoved)) {
                    count++;
                    prevloc = pdas->loc;
                }
                else if(pdas->val > firstMoved){
                    prevloc = MAX_VALS;
                    break;
                }
                else {
                    firstMoved = pdas->val;
                }
                pdas = pdas->pNext;
            }
            pdas = nxtpdas;
        }
        printf("%d %d\n", curprob, nvals - count);
    }
    return 0;
}
