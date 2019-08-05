#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_COUNT 100
char inbuf[256];
typedef unsigned char BYTE;

int gIndex, count;

typedef struct _fats_value_{
  struct _fats_value_ *next;  
  int hash; 
  int gIndex; 
  BYTE totDigitCount; 
  BYTE digitCounts[10];
} RATS_Value;

RATS_Value input;  
RATS_Value terms[MAX_COUNT]; 
RATS_Value *hashTable[129];  


void ClearAll(void){
  int i;
  memset(&(terms[0]), 0, MAX_COUNT*sizeof(RATS_Value));
  for(i = 0; i < 129 ; i++) hashTable[i] = NULL;
}
void ClearRATS(RATS_Value *pRV){
  int i;
  pRV->next = NULL;
  pRV->hash = 0;
  pRV->totDigitCount = 0;
  for(i = 0; i < 10 ; i++) {
    pRV->digitCounts[i] = 0;
  }
}
int ParseInput(char *buf){
  char *pb = buf;
  int hash, i;
  ClearRATS(&input);
  while((*pb != 0) && isspace(*pb)) pb++;
  if(!isdigit(*pb)) return -1;
  gIndex = 0;
  while(isdigit(*pb)) {
    gIndex = gIndex *10 + (*pb - '0');
    pb++;
  }
  while((*pb != 0) && isspace(*pb)) pb++;
  if(!isdigit(*pb)) return -2;
  count = 0;
  while(isdigit(*pb)) {
    count = count *10 + (*pb - '0');
    pb++;
  }
  while((*pb != 0) && isspace(*pb)) pb++;
  if(!isdigit(*pb)) return -3;
  while(isdigit(*pb)) {
    input.digitCounts[(*pb - '0')]++;
    input.totDigitCount++;
    pb++;
  }
  for(i = 0, hash = 0; i < 10 ; i++) {
    hash = hash*5 + input.digitCounts[i];
  }
  input.hash = hash;
  return 0;
}
int CheckCreeper(RATS_Value *pRV){
  if((pRV->digitCounts[1] == 1) && (pRV->digitCounts[2] == 1) && (pRV->digitCounts[3] >= 2) &&
    (pRV->digitCounts[4] == 4) && (pRV->digitCounts[5] == 0) && (pRV->digitCounts[6] == 0) &&
    (pRV->digitCounts[7] == 0) && (pRV->digitCounts[8] == 0) && (pRV->digitCounts[9] == 0)) {
    return 1;
  }
  if((pRV->digitCounts[1] == 0) && (pRV->digitCounts[2] == 0) && (pRV->digitCounts[3] == 0) &&
    (pRV->digitCounts[4] == 0) && (pRV->digitCounts[5] == 2) && (pRV->digitCounts[6] >= 2) &&
    (pRV->digitCounts[7] == 4) && (pRV->digitCounts[8] == 0) && (pRV->digitCounts[9] == 0)) {
    return 1;
  }
  return 0;
}
char outbuf[256];

char *OutRATSVal(RATS_Value *pRV){
  char *pb = &(outbuf[0]);
  int i, j;
  for(i = 1; i < 10 ; i++) {
    for(j = 0; j < pRV->digitCounts[i] ; j++) {
      *pb++ = i + '0';
    }
  }
  *pb = 0;
  return &(outbuf[0]);
}
int CompRATS(int gIndex){
  RATS_Value *pSrc, *pDest;
  int i1, i2, j1, j2, digcnt, carry, sum, hash;
  pSrc = &(terms[gIndex-1]);
  pDest = &(terms[gIndex]);
  ClearRATS(pDest);
  i1 = 1; i2 = 9; digcnt = pSrc->totDigitCount;
  j1 = 0; j2 = 0; carry = 0;
  while(digcnt > 0) { 
    digcnt--;
    while((i1 < 10) && (j1 >= pSrc->digitCounts[i1])){
      i1++;
      j1 = 0;
    }
    while((i2 > 0) && (j2 >= pSrc->digitCounts[i2])){
      i2--;
      j2 = 0;
    }
    sum = i1 + i2 + carry;
    pDest->digitCounts[sum%10]++;
    pDest->totDigitCount++;
    carry = sum/10;
    j1++, j2++; 
  }
  if(carry > 0){
    pDest->digitCounts[1]++;
    pDest->totDigitCount++;
  }
  pDest->totDigitCount -= pDest->digitCounts[0];
  pDest->digitCounts[0] = 0;
  for(i1 = 0, hash = 0; i1 < 10 ; i1++) {
    hash = hash*5 + pDest->digitCounts[i1];
  }
  pDest->hash = hash;
  pDest->gIndex = gIndex;
  return 0;
}
int CheckDup(int gIndex){
  int hind, i, ret;
  RATS_Value *pRV, *prev;
  hind = terms[gIndex].hash % 129;
  if(hashTable[hind] == NULL) {
    hashTable[hind] = &terms[gIndex];
    return 0;
  }
  pRV = hashTable[hind];
  while(pRV != NULL) {
    if(pRV->hash == terms[gIndex].hash) {
      ret = gIndex;
      for(i = 0; i < 10 ; i++) {
        if(pRV->digitCounts[i] != terms[gIndex].digitCounts[i]) {
          ret = 0;
          break;
        }
      }
      if(ret != 0) {
        return ret;
      }
    }
    prev = pRV;
    pRV = pRV->next;
  }
  prev->next = &(terms[gIndex]);
  return 0;
}
int main(){
  int nprob, curprob, ret, i;
  if(fgets(&(inbuf[0]), 255, stdin) == NULL)
  {
    fprintf(stderr, "Read failed on problem count\n");
    return -1;
  }
  if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)
  {
    fprintf(stderr, "Scan failed on problem count\n");
    return -2;
  }
  for(curprob = 1; curprob <= nprob ; curprob++)
  {
    if(fgets(&(inbuf[0]), 255, stdin) == NULL)
    {
      fprintf(stderr, "Read failed on problem %d header\n", curprob);
      return -3;
    }
    if((ret = ParseInput(&(inbuf[0]))) != 0) {
      fprintf(stderr, "scan failed on problem data problem gIndex %d\n",
        curprob);
      return -6;
    }
    if(gIndex != curprob)
    {
      fprintf(stderr, "problem gIndex %d not = expected problem %d\n",
        gIndex, curprob);
      return -7;
    }
    if(count > MAX_COUNT)
    {
      fprintf(stderr, "problem gIndex %d: count %d > max count %d\n",
        gIndex, count, MAX_COUNT);
      return -8;
    }
    if(CheckCreeper(&input)) {
      printf("%d C 1\n", gIndex);
    } else {
      ret = 0;
      ClearAll();
      terms[0] = input;
      terms[0].gIndex = 0;
      hashTable[input.hash % 129] = &(terms[0]);
      for(i = 1; (i < count) && (ret == 0) ; i++) {
        CompRATS(i);
        if((ret = CheckCreeper(&terms[i]))) {
          printf("%d C %d\n", gIndex, i+1);
        } else if((ret = CheckDup(i)) != 0) {
          printf("%d R %d\n", gIndex, i+1);
        }
      }
      if(ret == 0) {
        printf("%d %s\n", gIndex, OutRATSVal(&(terms[count-1])));
      }
    }
  }
  return 0;
}
