
bool good(int*v, int vSz, int a, int b, int k){
  if(b+k-1 >= vSz)
    return false;
  for(int i = 0; i < k; i++){
    if(v[a+i] != v[b+i])
      return false;
  }
  return true;
}
bool containsPattern(int*arr, int arrSz, int m, int k){
  for(int i = 0; i < arrSz; i++){
    int nummatch = 1;
    int j = i + m;
    while(j + m - 1 < arrSz){
      if(good(arr, arrSz, i, j, m)){
        nummatch++;
        j += m;
      }
      else{
        break;
      }
    }
    if(nummatch >= k)
      return true;
  }
  return false;
}
