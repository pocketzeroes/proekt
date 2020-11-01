typedef int* intp;
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return*a;
}
int cmpP(const void*pa, const void*pb){
  intp*aa = (intp*)pa;
  intp*bb = (intp*)pb;
  int*a=*aa;
  int*b=*bb;
  if(a[0] != b[0])return(a[0] < b[0])?-1:1;
  if(a[1] != b[1])return(a[1] < b[1])?-1:1;
  return 0;
}
int maxWidthOfVerticalArea(int**points, int pointsSz, int*points0sz){
  int i;
  int res = 0;
  qsort(points, pointsSz, sizeof(int*), cmpP);
  for(i=1; i<pointsSz; i++)
    chmax(&res, points[i][0] - points[i-1][0]);
  return res;
}
