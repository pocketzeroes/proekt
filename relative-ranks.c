int cmp(const void *p1, const void *p2) {
    const int *x = (const int *)p1;
    const int *y = (const int *)p2;
    return x[0] < y[0];
}
char** findRelativeRanks(int* nums, int numsSize, int* returnSize) {
    int numsIndex[numsSize][2];
    memset(numsIndex,0,sizeof(numsIndex));
    for (int i = 0; i < numsSize; ++i){
        numsIndex[i][0]=nums[i];
        numsIndex[i][1]=i;
    }
    qsort(numsIndex, numsSize, sizeof(numsIndex[0]), cmp);
    char**res=malloc(numsSize*sizeof(char*));
    char buff[32];
    for (int i = 0; i < numsSize; ++i) {
        sprintf(buff,"%d", i + 1);
        if (i == 0)      res[numsIndex[0][1]] = strdup("Gold Medal");
        else if (i == 1) res[numsIndex[1][1]] = strdup("Silver Medal");
        else if (i == 2) res[numsIndex[2][1]] = strdup("Bronze Medal");
        else             res[numsIndex[i][1]] = strdup(buff);
    }
   *returnSize=numsSize;
    return res;
}
