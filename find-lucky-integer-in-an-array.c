int findLucky(int*arr, int arrSz){
  int i;
  int cnt[501]={};
  int N = arrSz;
  for(i=0; i<N; i++)
    cnt[arr[i]]++;
  for(i=501-1; i>=1; i--)
    if(cnt[i]==i)
      return i;
  return-1;
}
