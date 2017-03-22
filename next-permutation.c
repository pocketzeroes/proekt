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
#if 0
int main(){
    int *aaa=malloc(3*sizeof(int));
    aaa[0]=1;
    aaa[1]=2;
    aaa[2]=3;
    nextPermutation(aaa, 3);
    printf("%d %d %d \n", aaa[0],aaa[1], aaa[2]);
}
#endif