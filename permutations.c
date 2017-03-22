#include <stdio.h>
#include<stdlib.h>
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
void nextPermutation(int* nums, int numsSize) {
    if( numsSize > 0){} else {
        return;
    }
    int violate = -1;
    for( int i=numsSize-1;i>0;i--){
        if( nums[i] > nums[i - 1] ){
            violate = i - 1;
            break;
        }
    }
    if( violate != -1 ){
        for(int i=numsSize-1;i>violate;i--){
            if( nums[i] > nums[violate] ){
                swap(nums, i, violate);
                break;
            }
        }
    } 
    reverse(nums, violate + 1, numsSize - 1);
}
int cmpInt(const void *a, const void *b) {   return *(int*)a - *(int*)b; }
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}
int** permute(int* nums, int numsSize, int* returnSize) {
    int fact = factorial(numsSize);
    qsort(nums, numsSize, sizeof(int), cmpInt);
    int**res=malloc(fact*sizeof(int*));
    for(int i=0;i<fact;i++){
        nextPermutation(nums,numsSize);
        int*elem=malloc(numsSize*sizeof(int));
        for(int j=0;j<numsSize;j++)elem[j]=nums[j];
        res[i]=elem;
    }
   *returnSize=fact;
    return res;
}

































