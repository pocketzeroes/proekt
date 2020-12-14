typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

int*getSumAbsoluteDifferences(int*nums, int numsSz, int*rsz){
  int n = numsSz;
  int*risan=calloc(n,sizeof(int));
  pair dat[n];
  int dsz=0;
  int tot = 0;
  for(int i=0; i<n; ++i){
    dat[dsz++] = newpair(nums[i],i);
    tot += nums[i];
  }
  qsort(dat, dsz, sizeof(pair), cmpP);
  int a = 0;
  int b = n - 1;
  int kecil = 0;
  for(int i=0; i<dsz; ++i){
    tot -= dat[i].first;
    int x = dat[i].first * a - kecil + tot - b * dat[i].first;
    ++a;
    --b;
    kecil += dat[i].first;
    risan[dat[i].second] = x;
  }
 *rsz=n;
  return risan;
}
