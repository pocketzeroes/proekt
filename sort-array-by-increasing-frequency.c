typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pb, const void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

void sortAL(int N, int*a, int*b){
  int i;
  pair arr[N];
  for(i=0; i<N; i++){
    arr[i].first  = a[i];
    arr[i].second = b[i];
  }
  qsort(arr, N, sizeof(pair), cmpP);//rev
  for(i=0; i<N; i++)
    b[i] = arr[i].second;
}
int v[100];
int f[100];
int fre[201];

int*frequencySort(int*A, int Asz, int*rsz){
  int i;
  int N = Asz;
  int*res=calloc(N, sizeof(int));
  for(i=0; i<201; i++)
    fre[i] = 0;
  for(i=0; i<N; i++)
    fre[A[i]+100]--;
  for(i=0; i<N; i++){
    {
      int FmcKpFmN = (A[i]);
      int xr20shxY = ( fre[A[i]+100]);
      v[i] = FmcKpFmN;
      f[i] = xr20shxY;
    }
  }
  sortAL(N, f, v);//rev
  for(i=0; i<N; i++)
    res[i] = v[i];
 *rsz=N;
  return res;
}
