int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

int*sortArray(int*nums, int numsSz, int*rsz){
    int*rv = calloc(numsSz, sizeof(int));
    for(int i=0; i<numsSz; i++)
        rv[i] = nums[i];
    qsort(rv, numsSz, sizeof(int), cmp);
   *rsz=numsSz;
    return rv;
}

