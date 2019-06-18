typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int largestValsFromLabels(int*values, int valuesSz, int*labels, int labelsSz, int num_wanted, int use_limit){
  int n = valuesSz;
  pair ai[n];
  for(int i = 0; i < n; i++){
    ai[i] = newPair(values[i], labels[i]);
  }
  int cmpP(const void*pa, const void*pb){
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    return a->first - b->first;
  }
  qsort(ai, n, sizeof(pair), cmpP);
  int f[50000] = {0};
  int sum  = 0;
  int used = 0;
  for(int i = n-1; i >= 0; i--){
    if(used < num_wanted && ++f[ai[i].second] <= use_limit){
      sum += ai[i].first;
      used++;
    }
  }
  return sum;
}
