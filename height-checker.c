int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int heightChecker(int*heights, int heightsSz){
    int*x = calloc(heightsSz, sizeof(int));
    for(int i=0;i<heightsSz;i++)
        x[i] = heights[i];
    qsort(x, heightsSz, sizeof(int), cmp);
    int ans = 0;
    for(int i=0; i<heightsSz; i++)
        ans += x[i] != heights[i];
    return ans;
}
