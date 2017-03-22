#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRIME_NUMBER 256203161
#define MAX_SZ 40096



int hashes[MAX_SZ];
int hnum;
int cols[MAX_SZ];
int a[512];

int**findSubsequences(int*nums,int numsSz,int**cSizes,int*rsz){
  hnum=0;
  memset(hashes,0,sizeof(hashes));
  int n = numsSz;
  int**r=malloc(MAX_SZ*sizeof(int*));
  int rLen=0;
  int c=0;
  int aSz=0;
  for(int i = 0; i < (1<<n); i++) {
    int last = -1000;
    aSz=0;
    for(int j = 0; j < n; j++)
      if (i>>j&1) {
        if (last > nums[j])
          goto out;
        last = nums[j];
        a[aSz++]= nums[j];
      }
    if(aSz > 1){
      unsigned hash1 = PRIME_NUMBER;
      for (int j = 0; j < aSz; j++)
        hash1 = hash1 * PRIME_NUMBER + a[j];
      int unique=1;
      for( int i=0;i<hnum;i++){
          if(hashes[i]==hash1){
             unique=0;
             break;
          }
      }
      if(unique){
        int*ha=malloc(aSz*sizeof(int)); 
        for(int z=0;z<aSz;z++)ha[z]=a[z];
        r[rLen++]=ha;
        cols[c++]= aSz;
        hashes[hnum++]=hash1;
      }
    }
out:;;
  }
  int*hcols=malloc(rLen*sizeof(int));
  for(int i=0;i<rLen;i++)hcols[i]=cols[i];
 *cSizes=hcols;
 *rsz=rLen;
  return r;
}
#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )
#if 0
int main() {
int nums[] = {-78,-90,65,-78,19,-78,-4,18,7,-33,-19,-26,-19,10,-30};
  int numsSize = countof(nums);
  int *cols;
  int returnSize;
  int**rez=findSubsequences(nums, numsSize, &cols, &returnSize);
  for(int i=0;i<returnSize;i++){
      for(int j=0;j<cols[i];j++)
          printf("%d ",rez[i][j]);
      printf("\n");
  }
  return 0;
}
#endif
    

     



