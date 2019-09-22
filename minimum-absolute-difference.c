int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef int* intp;
///////////////////////
intp*ans;
int  asz;
int**minimumAbsDifference(int*arr, int arrSz, int*rsz, int**csz){
    asz=0;
    ans = calloc(arrSz, sizeof(intp));
    qsort(arr, arrSz, sizeof(int), cmp);
    int n = arrSz, i, j, k, minn = 1000000000;
    for (i = 1; i < n; i++)
        minn = fmin(minn, arr[i] - arr[i - 1]);
    for (i = 1; i < n; i++){
        if (arr[i] - arr[i - 1] == minn){
            int*s=calloc(2,sizeof(int));
            s[0]=arr[i-1];
            s[1]=arr[i];
            ans[asz++] = s;
        }
    }
    int*cols=calloc(asz, (sizeof(int)));
    fill(cols, asz, 2);
   *csz = cols;
   *rsz = asz;
    return ans;
}
