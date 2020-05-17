
double max_L(double a, double b){
  return a>=b?a:b;
}
double pow2_L(double a){
  return a*a;
}
int chmax(int*a, int b){
  if(*a<b)
     *a=b;
  return *a;
}
#define EPS 1e-9
int N;
double X[100];
double Y[100];
int calc(double cx, double cy, double r){
  int i;
  int res = 0;
  double d;
  for(i=(0);i<(N);i++){
    d = sqrt((pow2_L((X[i]-cx)))+(pow2_L((Y[i]-cy))));
    if(d <= r+EPS)
      res++;
  }
  return res;
}

int numPoints(int**points, int pointsSz, int*points0sz, int r){
  int i;
  int res = 1;
  double cx;
  double cy;
  double dx;
  double dy;
  double d;
  double len;
  N = pointsSz;
  for(i=0; i<N; i++){
    int cTE1_r3A = (points[i][0]);
    int RZTsC2BF = ( points[i][1]);
    X[i] = cTE1_r3A;
    Y[i] = RZTsC2BF;
  }
  for(i=0; i<N; i++)
    chmax(&res, calc(X[i], Y[i], r));
  for(i=0; i<N; i++){
    int j;
    for(j=i+1; j<N; j++){
      if(X[i]==X[j] && Y[i]==Y[j])
        continue;
      cx = (X[i]+X[j]) / 2;
      cy = (Y[i]+Y[j]) / 2;
      dx = Y[j] - Y[i];
      dy = -(X[j] - X[i]);
      len = sqrt((pow2_L(dx))+(pow2_L(dy)));
      {
        double tU__gIr_ = (len);
        dx /= tU__gIr_;
        dy /= tU__gIr_;
      }
      d = sqrt((pow2_L((X[i]-cx)))+(pow2_L((Y[i]-cy))));
      len = r*r - d*d;
      if(len < -EPS)
        continue;
      len = sqrt(max_L(len, 0.0));
      chmax(&res, calc(cx+len*dx, cy+len*dy, r));
      chmax(&res, calc(cx-len*dx, cy-len*dy, r));
    }
  }
  return res;
}
