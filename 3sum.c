#include<stdio.h>
#include<stdlib.h>


int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int** threeSum(int* nums, int numsSize, int* returnSize){
    int**ansList=malloc(1000000);
    int  ansListSz=0;
    int length = numsSize;
    qsort(nums, numsSize, sizeof(int),&cmpfunc);
    int last_head = INT_MAX;
    for(int i = 0; i < length - 2; i++ ){
        int low      = i + 1; 
        int high     = length - 1;
        int sum      = 0 - nums[i];
        int*last_ans = NULL;
        if( last_head == nums[i] ){
            continue;
        }
        last_head = nums[i];
        for(;;) {
            if( low >= high )
                break;
            int diff = nums[low] + nums[high];
            if( diff == sum){
              if( last_ans && (last_ans[1] == nums[low] || last_ans[1] == nums[high] ) ){
                  low++;
                  high--;
                  continue;
              }
              int*ans=malloc(3*sizeof(int));
              ans[0]=nums[i   ];
              ans[1]=nums[low ];
              ans[2]=nums[high];
              qsort(ans, 3, sizeof(int),&cmpfunc);
//            printf("%d %d %d \n",ans[0],ans[1],ans[2]);
              ansList[ansListSz++] =ans;
              last_ans = ans;
              low++;
              high--;
            }
            else if( diff < sum)
              low++;
            else if( diff > sum)
              high--;
        }
    }
    
    *returnSize=ansListSz;
    return ansList;
}
// [-1,0,1,2,-1,-4]
#if 0
int main(int argc, char**argv){
    int arr[]={-1, 0, 1, 2,-1,-4};
    int sz;
    threeSum(arr, 6, &sz);
    puts("done");
}
#endif


