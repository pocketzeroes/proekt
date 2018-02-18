int min(int a,int b){return a<b?a:b;}
int upper_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if (x >= a[mid])
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}

int p,q;
int gAsz;
int count(int*A, double mid){
    int n = gAsz;
    p=0;
    q=1;
    int ret=0;
    for(int i=0; i<n; i++){
        double mx=mid*A[i];
        int ub = upper_bound(A, gAsz, mx);
        int it = ub-1;
        it = min(it, i-1);
        if(it>=0){
            if(A[it]*q > p*A[i]){
                p = A[it];
                q = A[i];
            }
        }
        ret += it+1;
    }
    return ret;
}
int*kthSmallestPrimeFraction(int*A, int Asz, int K, int*rsz){
    gAsz = Asz;
    double s=0, t=1;
    int ansP, ansQ;
    while(s+(1e-8)<t){
        double mid=(s+t)/2;
        if(count(A,mid)<=K){
            s=mid;
            ansP=p;
            ansQ=q;
        }
        else t=mid;
    }
    int*ret = calloc(2, sizeof(int)); *rsz = 2;
    ret[0]=ansP;
    ret[1]=ansQ;
    return ret;
}
