int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int stoneGameVI(int*aliceValues, int aliceValuesSz, int*bobValues, int bobValuesSz){
  int n = aliceValuesSz;
  int s[n];
  for(int i=0;i<n;++i)
    s[i] = -aliceValues[i]-bobValues[i];
  qsort(s, n, sizeof(int), cmp);
  int risan = 0;
  for(int i=0; i<n; ++i)
    risan += aliceValues[i];
  for(int i=0; i<n; ++i)
    if(i % 2 == 1)
      risan += s[i];
  return risan == 0 ? 0 : ( risan > 0 ? 1 : -1);
}
