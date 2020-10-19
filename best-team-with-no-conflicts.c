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

int bestTeamScore(int*scores, int scoresSz, int*ages, int agesSz){
    int n = scoresSz;
    pair a[n];
    int f[1010];
    int i, j;
    for(i=0; i<n; ++i)
        a[i]=(pair){ages[i], scores[i]};
    qsort(a, n, sizeof(pair), cmpP);
    int res=0;
    for(i=0; i<n; ++i){
        f[i] = a[i].second;
        for(j=0; j<i; ++j){
            if(a[j].second > a[i].second)
                continue;
            f[i] = fmax(f[i], f[j] + a[i].second);
        }
        res = fmax(res, f[i]);
    }
    return res;
}
