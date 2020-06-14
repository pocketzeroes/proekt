int cmp (const void*a, const void*b){ return(*(int*)a-*(int*)b);}
int cmpR(const void*b, const void*a){ return(*(int*)a-*(int*)b);}

int runLength(int N, int*arr, void*val_s, void*len_s){
  int i;
  int rN;
  int *val = (int*) val_s;
  int *len = (int*) len_s;
  if(N==0)
    return 0;
  rN = 1;
  val[0] = arr[0];
  len[0] = 1;
  for(i=1; i<N; i++){
    if(val[rN-1] == arr[i])
      len[rN-1]++;
    else{
      val[rN] = arr[i];
      len[rN] = 1;
      rN++;
    }
  }
  return rN;
}

int A  [100000];
int val[100000];
int len[100000];

int findLeastNumOfUniqueInts(int*arr, int arrSz, int k){
  int i;
  int sz;
  int N = arrSz;
  for(i=0; i<N; i++)
    A[i] = arr[i];
  qsort(A, N, sizeof(int), cmp);
  sz = runLength(N, A, val, len);
  qsort(len, sz, sizeof(int), cmpR);
  while(sz && len[sz-1] <= k){
    k -= len[sz-1];
    sz--;
  }
  return sz;
}
