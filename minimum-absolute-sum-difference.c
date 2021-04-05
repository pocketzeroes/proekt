typedef long long ll;
#define MD (1000000007U)
ll chmin(ll*a, ll b){
  if(*a>b){
    *a=b;
  }
  return *a;
}
ll chmax(ll*a, ll b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

ll d[100000+1];

int minAbsoluteSumDiff(int*A, int Asz, int*B, int Bsz){
  int i;
  ll res = 0;
  ll mx = 0;
  ll tmp;
  for(i=(0);i<(100000+1);i++){
    d[i] = 4611686016279904256LL;
  }
  for(i=(0);i<(Asz);i++){
    d[A[i]] = 0;
  }
  for(i=(1);i<(100000+1);i++){
    chmin(&d[i], d[i-1] + 1);
  }
  for(i=(100000+1)-1;i>=(1);i--){
    chmin(&d[i-1], d[i] + 1);
  }
  for(i=(0);i<(Asz);i++){
    tmp = abs(A[i] - B[i]);
    res += tmp;
    chmax(&mx, tmp - d[B[i]]);
  }
  res -= mx;
  return res % MD;
}
