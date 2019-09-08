int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int gain[10000];
int maximumNumberOfOnes(int X, int Y, int S, int M){
  int i, j, res=0;
  for(i=0;i<(S);i++){
    for(j=0;j<(S);j++){
      gain[i*S+j] = 0;
    }
  }
  for(i=0;i<(X);i++){
    for(j=0;j<(Y);j++){
      gain[ (i%S)*S + (j%S) ]++;
    }
  }
  qsort(gain, S*S, sizeof(int), cmp);
  for(i=0;i<(M);i++){
    res += gain[S*S-1-i];
  }
  return res;
}
