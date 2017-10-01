int cmpVec(int*a, int*b){
  int msz = 3;
  for(int i=0;i < msz; i++){
    if(a[i] != b[i]) 
      return (a[i] < b[i])?-1:1;
  }
  return 0;
}
int*maxSumOfThreeSubarrays(int*a, int aSz, int k, int*rsz){
    int n = aSz;
    int sum[n + 1];
    sum[0] = 0;
    for (int i = 0; i < n; ++i) 
        sum[i + 1] = sum[i] + a[i];
    int A [n];
    int rA[n];
    int cur = 0;
    for (int i = 0; i < k; ++i) 
        cur += a[i];
    A[k - 1] = cur; 
    rA[k - 1] = 0;
    for (int i = k; i < n; ++i) {
        cur -= a[i - k];
        cur += a[i];
        if (cur > A[i - 1]) {
            A[i] = cur;
            rA[i] = i - k + 1;
        } 
        else {
            A[i] = A[i - 1];
            rA[i] = rA[i - 1];
        }
    }
    int B [n];
    int rB[n];
    cur = 0;
    for (int i = 0; i < k; ++i) 
        cur += a[n - 1 - i];
    B [n - k] = cur; 
    rB[n - k] = n - k;
    for (int i = n - k - 1; i >= 0; --i) {
        cur -= a[i + k];
        cur += a[i];
        if (cur >= B[i + 1]) {
            B[i] = cur;
            rB[i] = i;
        } 
        else {
            B[i] = B[i + 1];
            rB[i] = rB[i + 1];
        }
    }
    int best = 0;
    int*ret = calloc(3, sizeof(int));
    for(int i = k; i + k + k <= n; ++i){
        int cur = sum[i + k] - sum[i] + A[i - 1] + B[i + k];
        int*now = calloc(3, sizeof(int));
        now[0]=rA[i - 1];
        now[1]= i;
        now[2]=rB[i + k];
        if (cur > best || (cur == best && cmpVec(now, ret)<0 )){
            best = cur;
            memcpy(ret, now, 3*sizeof(int));
        }
    }
   *rsz = 3;
    return ret;
}



























