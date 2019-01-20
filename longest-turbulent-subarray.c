inline int max(int a,int b){return a>b?a:b;}

int maxTurbulenceSize(int*A, int Asz){
  int cur=0, ma=0, i;
  for(i=0; i<Asz-1; i++){
    if(i%2==0) {
      if(A[i]<A[i+1]) 
        cur++;
      else
        cur=0;
    }
    else {
      if(A[i]>A[i+1]) 
        cur++;
      else
        cur=0;
    }
    ma = max(ma,cur);
  }
  cur=0;
  for(i=0; i<Asz-1; i++){
    if(i%2==1){
      if(A[i]<A[i+1])
        cur++;
      else
        cur=0;
    }
    else{
      if(A[i]>A[i+1])
        cur++;
      else
        cur=0;
    }
    ma=max(ma,cur);
  }
  return ma+1;
}
