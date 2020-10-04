int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}
void arrInsert(int k, int*sz, double*a, double aval, double*b, double bval){
  int i;
  (*sz)++;
  for(i=k-1;i>k;i--){
    a[i] = a[i-1];
  }
  for(i=k-1;i>k;i--){
    b[i] = b[i-1];
  }
  a[k] = aval;
  b[k] = bval;
}
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

#define EPS 1e-13
double x[100000];
double y[100000];
double th[200000];

int visiblePoints(int**points, int pointsSz, int*points0sz, int angle, int*location, int locationSz){
  int res = 0;
  int ad = 0;
  int n = pointsSz;
  int i;
  int j;
  int k;
  double ang;
  for(i=(0);i<(n);i++){
    {
      int Q5VJL1cS = (points[i][0] - location[0]);
      int e98WHCEY = (points[i][1] - location[1]);
      x[i] = Q5VJL1cS;
      y[i] = e98WHCEY;
    }
  }
  k = 0;
  for(i=(0);i<(n);i++){
    if(x[i]==0 && y[i]==0){
      ad++;
      continue;
    }
    arrInsert(k, &k, x, x[i], y, y[i]);
  }
  n = k;
  for(i=(0);i<(n);i++){
    th[i] = atan2(y[i], x[i]);
  }
  qsort(th, n, sizeof(double), cmpDbl);
  for(i=(0);i<(n);i++){
    th[n+i] = th[i] + 2 * M_PI;
  }
  ang = angle * M_PI / 180 + EPS;
  j = 0;
  for(i=(0);i<(n);i++){
    while(j < 2*n && th[j] < th[i] + ang){
      j++;
    }
    chmax(&res, j - i);
  }
  return res + ad;
}
