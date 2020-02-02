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

int*kWeakestRows(int**mat, int matSz, int*mat0sz, int k, int*rsz){
    int m = matSz;
    pair v[m];
    for(int i=0; i<m; ++i){
        int c=0;
        for(int j=0; j<mat0sz[i]; ++j)
            c+=mat[i][j];
        v[i] = newpair(c, i);
    }
    qsort(v, m, sizeof(pair), cmpP);
    int*r = calloc(k, sizeof(int));
    for(int i=0; i<k; ++i)
        r[i] = v[i].second;
   *rsz = k;
    return r;
}
