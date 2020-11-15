int*decrypt(int*code, int codeSz, int k, int*rsz){
  int n = codeSz, i, j;
  int*a = calloc(n, sizeof(int));
  for(i = 0; i < n; i++) {
    if(k > 0) {
      for (j = 1; j <= k; j++) a[i] += code[(i + j) % n];
    }
    if(k < 0) {
      for(j = 1; j <= -k; j++) a[i] += code[(i - j + n) % n];
    }
  }
  *rsz=n;
  return a;
}
