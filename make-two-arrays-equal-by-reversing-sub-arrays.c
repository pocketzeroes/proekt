int cmp(const void*a, const void*b){
  return(*(int*)a-*(int*)b);
}
bool canBeEqual(int*target, int targetSz, int*arr, int arrSz){
  qsort(target, targetSz, sizeof(int), cmp);
  qsort(arr   , arrSz   , sizeof(int), cmp);
  return memcmp(target, arr, arrSz*sizeof(int))==0;
}
