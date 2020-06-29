int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

int Factor_L(int N, int fac[], int fs[]){
  int i;
  int sz = 0;
  if(N%2==0){
    fac[sz] = 2;
    fs[sz] = 1;
    N /= 2;
    while(N%2==0){
      N /= 2;
      fs[sz]++;
    }
    sz++;
  }
  for(i=3;i*i<=N;i+=2){
    if(N%i==0){
      fac[sz] = i;
      fs[sz] = 1;
      N /= i;
      while(N%i==0){
        N /= i;
        fs[sz]++;
      }
      sz++;
    }
  }
  if(N > 1){
    fac[sz] = N;
    fs[sz] = 1;
    sz++;
  }
  return sz;
}
int Divisor_L(int N, int res[]){
  int i;
  int j;
  int k;
  int s;
  int sz = 0;
  int *fc;
  int *fs;
  int fsz;
  fc=calloc(100, sizeof(int));
  fs=calloc(100, sizeof(int));
  fsz =Factor_L(N, fc, fs);
  res[sz++] = 1;
  for(i=(0);i<(fsz);i++){
    s = sz;
    k = s * fs[i];
    for(j=(0);j<(k);j++){
      res[sz++] = res[j] * fc[i];
    }
  }
  qsort(res, sz, sizeof(int), cmp);
  return sz;
}


int ys;
int y[1000];

int kthFactor(int n, int k){
  ys =Divisor_L(n, y);
  if(k-1 >= ys)
    return -1;
  return y[k-1];
}
