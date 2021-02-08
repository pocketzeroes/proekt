typedef long long ll;
ll**newmat(int x, int y){
  ll**rv = calloc(x, sizeof(ll*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(ll));
  return rv;
}
void freemat(ll**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

typedef struct{
  int first;
  int second;
}pair;
typedef struct{
  int  first;
  pair second;
}trip;
int cmpP(const void*pa, const void*pb){
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)
    return(a->first < b->first )?-1:1;
  return cmpP(&a->second, &b->second);
}

void sortA_L(int N, int*a, int*b, int*c){
  int i;
  trip*arr=calloc(N, sizeof(trip));
  for(i=(0);i<(N);i++){
    arr[i].first = a[i];
    arr[i].second.first = b[i];
    arr[i].second.second = c[i];
  }
  qsort(arr, N, sizeof(trip), cmpT);
  for(i=(0);i<(N);i++){
    a[i] = arr[i].first;
    b[i] = arr[i].second.first;
    c[i] = arr[i].second.second;
  }
  free(arr);
}
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}
int coordcomp_L(int n1, int*arr1, int n2, int*arr2){
  int i;
  int k = 0;
  pair*r=calloc(n1+n2, sizeof(pair));
  for(i=(0);i<(n1);i++){
    r[i].first = arr1[i];
    r[i].second = i;
  }
  for(i=(0);i<(n2);i++){
    r[n1+i].first = arr2[i];
    r[n1+i].second = n1+i;
  }
  qsort(r, n1+n2, sizeof(pair), cmpP);
  for(i=(0);i<(n1+n2);i++){
    if(i && r[i].first != r[i-1].first){
      k++;
    }
    if(r[i].second < n1){
      arr1[r[i].second] = k;
    }
    else{
      arr2[r[i].second-n1] = k;
    }
  }
  free(r);
  return k+1;
}

int N;
int K;
int A[1000000];
int B[1000000];
int C[1000000];
int sz;
ll**dp;

int maxValue(int**events, int eventsSz, int*events0sz, int k){
  int i;
  int res = 0;
  int m = 0;
  N = eventsSz;
  K = k;
  for(i=(0);i<(N);i++){
    {
      int Q5VJL1cS = (events[i][0]);
      int e98WHCEY = (events[i][1]+1);
      int cTE1_r3A = (events[i][2]);
      A[i] = Q5VJL1cS;
      B[i] = e98WHCEY;
      C[i] = cTE1_r3A;
    }
  }
  sz = coordcomp_L(N, A, N, B);
  sortA_L(N, A, B, C);
  dp = newmat(K+1, sz);
  for(i=(0);i<(K+1);i++){
    int j;
    for(j=(0);j<(sz);j++){
      dp[i][j] = 0;
    }
  }
  for(k=(0);k<(N);k++){
    while(m < A[k]){
      for(i=(0);i<(K+1);i++){
        chmax(&dp[i][m+1], dp[i][m]);
      }
      m++;
    }
    for(i=(0);i<(K);i++){
      chmax(&dp[i+1][B[k]], dp[i][A[k]] + C[k]);
    }
  }
  for(i=(0);i<(K+1);i++){
    int j;
    for(j=(0);j<(sz);j++){
      chmax(&res, dp[i][j]);
    }
  }
  freemat(dp, K+1);
  return res;
}
