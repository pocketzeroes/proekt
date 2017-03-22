void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
typedef struct {
   int a; 
} Solution;
Solution*ptr;
int*gNums;
int*gCopy;
int gSize;

Solution* solutionCreate(int* nums, int size) {
    gNums=malloc(size*sizeof(int));
    for (int i=0;i<size;i++)
        gNums[i]=nums[i];
    gCopy=malloc(size*sizeof(int));
    for (int i=0;i<size;i++)
        gCopy[i]=nums[i];
    gSize=size;
    return ptr;
}

int* solutionReset(Solution* obj, int *returnSize) {
   *returnSize=gSize;
    return gNums;
}

int* solutionShuffle(Solution* obj, int *returnSize) {
    for (int i = 0;i < gSize;i++){
        int pos = rand()%(gSize-i);
        swap(gCopy, i+pos, i);
    }
   *returnSize=gSize;
    return gCopy;
}

void solutionFree(Solution* obj) {
    free(gNums); gNums=NULL;
    free(gCopy); gCopy=NULL;
    gSize=0;
}



























