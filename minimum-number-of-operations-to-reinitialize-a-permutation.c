

int a[1000];
int b[1000];

int reinitializePermutation(int n){
  int i;
  int res = 0;
  for(i=(0);i<(n);i++){
    a[i] = i;
  }
  for(;;){
    for(i=(0);i<(n/2);i++){
      b[i] = a[2*i];
    }
    for(i=(0);i<(n/2);i++){
      b[i+n/2] = a[2*i+1];
    }
    for(i=(0);i<(n);i++){
      a[i] = b[i];
    }
    res++;
    for(i=(0);i<(n);i++){
      if(a[i] != i){
        break;
      }
    }
    if(i==n){
      break;
    }
  }
  return res;
}
