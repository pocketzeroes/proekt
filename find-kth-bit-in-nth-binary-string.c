int sz;
int arr[3000000];

char findKthBit(int n, int k){
  int i;
  int t;
  if(sz==0){
    int Lj4PdHRW;
    arr[sz++] = 0;
    for(Lj4PdHRW=(0);Lj4PdHRW<(20);Lj4PdHRW++){
      t = sz;
      arr[sz++] = 1;
      for(i=(0);i<(t);i++){
        arr[sz++] = 1 - arr[t-1-i];
      }
    }
  }
  return arr[k-1] + '0';
}
