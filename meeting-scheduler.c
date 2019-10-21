typedef int* intp;

int cmpP(const void*pa, const void*pb){
  intp*aa = (intp*)pa;
  intp*bb = (intp*)pb;
  intp a = *aa;
  intp b = *bb;
  if(a[0] != b[0]) return(a[0] < b[0])?-1:1;
  if(a[1] != b[1]) return(a[1] < b[1])?-1:1;
  return 0;
}

int*minAvailableDuration(int**A, int Asz, int*A0sz, int**B, int Bsz, int*B0sz, int D, int*rsz){
  int mn;
  int mx;
  int a  = 0;
  int As = Asz;
  int b  = 0;
  int Bs = Bsz;
  qsort(A, Asz, sizeof(int*), cmpP);
  qsort(B, Bsz, sizeof(int*), cmpP);
  while(a < As && b < Bs){
    mn = fmax(A[a][0], B[b][0]);
    mx = fmin(A[a][1], B[b][1]);
    if(mn + D <= mx){
      int*rv = calloc(2, sizeof(int));
      rv[0] = mn;
      rv[1] = mn+D;
     *rsz=2;
      return rv;
    }
    if(A[a][1] == mx)
      a++;
    if(B[b][1] == mx)
      b++;
  }
  int*rv = calloc(2, sizeof(int));
 *rsz=0;
  return rv;
}
