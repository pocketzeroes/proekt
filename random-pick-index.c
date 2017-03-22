typedef struct {
    int a;
} Solution;
Solution*ptr;
int*gNums;
int gNumsSz;
Solution* solutionCreate(int* nums, int numsSize){
    gNums=malloc(numsSize*sizeof(int));
    for (int i=0;i<numsSize;i++)
        gNums[i]=nums[i];
    gNumsSz=numsSize;
    return ptr;
}
int solutionPick(Solution* obj, int target) {
    auto reservoir = -1;
    int n = 0;
    for (int i = 0; i < gNumsSz; ++i) {
        if (gNums[i] != target) 
            continue;
        if (++n == 1 || rand() % n == 0) 
            reservoir = i;
    }
    return reservoir;
}
void solutionFree(Solution* obj) {
    free(gNums);
    gNums=NULL;
    gNumsSz=0;
}


