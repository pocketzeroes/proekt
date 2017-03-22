#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmp(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    int diff=pa[0]-pb[0];
    if(diff==0)return pa[1]-pb[1];
    return diff;
}
typedef struct Interval Interval ;
int*findRightInterval(Interval*intervals,int intSz,int*rsz) {
    int**s=malloc(intSz*sizeof(int*));
    for(int i=0;i<intSz;i++){
      s[i]=malloc(2*sizeof(int));
      s[i][0]=0;
      s[i][1]=0;
    }
    int*res=NULL;
    int n = intSz;
    for (int i = 0; i < n; ++i) {
        Interval cur=intervals[i];
        s[i][0] = cur.start;
        s[i][1] = i;
    }
    qsort(s,intSz,2*sizeof(int),cmp);
    for(int i=0;i<intSz;i++){ 
        Interval in=intervals[i];
        int l = 0;
        int hi = intSz - 1;
        while (l < hi) {
            int mid = (l + hi) / 2;
            if (s[mid][0] < in.end) 
                l = mid + 1; 
            else 
                hi = mid; 
        }
        if (s[l][0] < in.end)
            res=pushback(res,rsz,-1);
        else 
            res=pushback(res,rsz,s[l][1]);
    }
    return res;
}





