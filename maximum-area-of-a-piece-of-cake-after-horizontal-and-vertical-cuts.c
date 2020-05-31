int cmp(const void * a, const void * b){
   return( *(int*)a - *(int*)b );
}

int maxArea(int h, int w, int*horizontalCuts, int horizontalCutsSz, int*verticalCuts, int verticalCutsSz){
    qsort(horizontalCuts, horizontalCutsSz, sizeof(int), cmp);
    qsort(verticalCuts  , verticalCutsSz  , sizeof(int), cmp);
    int hmax = fmax(horizontalCuts[0], h - horizontalCuts[horizontalCutsSz-1]);
    for(int i=0; i<horizontalCutsSz-1; i++)
        hmax = fmax(hmax, horizontalCuts[i+1] - horizontalCuts[i]);
    int vmax = fmax(verticalCuts[0], w - verticalCuts[verticalCutsSz-1]);
    for(int i=0; i<verticalCutsSz-1; i++)
        vmax = fmax(vmax, verticalCuts[i+1] - verticalCuts[i]);
    return(int)((long long)hmax*vmax % 1000000007);
}
