int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void wiggleSort(int*nums,int numsSz) {
    int*sorted=malloc(numsSz*sizeof(int));
    for(int i=0;i<numsSz;i++)sorted[i]=nums[i];
    int mid = (numsSz - 1) / 2;
    qsort(sorted,numsSz,sizeof(int),cmp);
    for (int i=numsSz-1, j=0, k=i/2+1; i>=0; i--)
        nums[i] = sorted[i&1 ? k++ : j++];
}
