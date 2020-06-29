
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
  for(i=(1);i<(N);i++){
    if(val[rN-1] == arr[i]){
      len[rN-1]++;
    }
    else{
      val[rN] = arr[i];
      len[rN] = 1;
      rN++;
    }
  }
  return rN;
}
int chmax(int*a, int b){
  if(*a<b)
    *a=b;
  return a;
}

int N;
int A[100000];
int sz;
int val[100000];
int len[100000];


int longestSubarray(int*nums, int numsSz){
  int i;
  int res = 0;
  N = numsSz;
  for(i=0; i<N; i++)
    A[i] = nums[i];
  sz = runLength(N, A, val, len);
  for(i=0; i<sz; i++)
    if(val[i]==1)
      chmax(&res, len[i] - 1);
  for(i=0; i<sz; i++)
    if(sz > 1 && val[i]==1)
      chmax(&res, len[i]);
  for(i=1; i<sz-1; i++)
    if(val[i]==0 && len[i]==1)
      chmax(&res, len[i-1] + len[i+1]);
  return res;
}
