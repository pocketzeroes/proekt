int maximizeSweetness(int*A, int Asz, int K){
  int N = Asz;
  int p;
  int cur;
  int res;
  int bahur;
  int mura;
  int zele;
  bahur = 1;
  mura = 1000000000;
  while(bahur < mura){
    int i;
    if((bahur + mura)%2==0)
      zele = (bahur + mura) / 2;
    else
      zele = (bahur + mura + 1) / 2;
    p = cur = 0;
    for(i=(0);i<(N);i++){
      cur += A[i];
      if(cur >= zele){
        cur = 0;
        p++;
      }
    }
    if(p >= K+1)
      bahur = zele;
    else
      mura = zele - 1;
  }
  res =mura;
  return res;
}
