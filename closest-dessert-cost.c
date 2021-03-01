
void DigitF_L(int n, int sz, int*res, int b){
  int i;
  for(i=(0);i<(sz);i++){
    res[i] = n % b;
    n /= b;
  }
}

int arr[10];
int pw[11];
int sz;
int c[1000000];

int closestCost(int*A, int Asz, int*B, int Bsz, int T){
  int i, mask;
  int N = Asz;
  int M = Bsz;
  int res;
  int opt = 1073709056;
  int tmp;
  int sa;
  pw[0] = 1;
  for(i=(0);i<(M);i++){
    pw[i+1] = pw[i] * 3;
  }
  sz = 0;
  for(mask=(0);mask<(pw[M]);mask++){
    DigitF_L(mask, M, arr, 3);
    int cTE1_r3A;
    int RZTsC2BF; // ll
    int FmcKpFmN = 0;
    if((0) > ((M)-1)){
      RZTsC2BF = 0;
    }
    else{
      for(cTE1_r3A = 0; cTE1_r3A <= (M)-1; cTE1_r3A++){
        if(FmcKpFmN == 0){
          RZTsC2BF = B[cTE1_r3A] * arr[cTE1_r3A];
          FmcKpFmN = 1;
          continue;
        }
        RZTsC2BF += B[cTE1_r3A] * arr[cTE1_r3A];
      }
    }
    c[sz++] =RZTsC2BF;
  }
  for(i=(0);i<(N);i++){
    int j;
    for(j=(0);j<(sz);j++){
      tmp = A[i] + c[j];
      sa = abs(T - tmp);
      if(sa < opt || (sa == opt && tmp < res)){
        res = tmp;
        opt = sa;
      }
    }
  }
  return res;
}

