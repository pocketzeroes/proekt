int chmax(int*a, int b){
  if(*a<b)
    *a=b;
  return *a;
}

int countGoodRectangles(int**A, int Asz, int*A0sz){
  int i;
  int mx  = 0;
  int res = 0;
  for(i=0; i<Asz;i++)
    chmax(&mx, fmin(A[i][0], A[i][1]));
  for(i=0; i<Asz; i++)
    if(mx == fmin(A[i][0], A[i][1]))
      res++;
  return res;
}
