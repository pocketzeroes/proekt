#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef struct{
  int first, second;
}pair;

int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

int*arrayRankTransform(int*arr, int arrSz, int*rsz){
    int n = arrSz;
    int*sol=calloc(n, sizeof(int));
    if(n==0){
       *rsz=0;
        return sol;
    }
    pair z[n]; clr(z);
    for(int i=0; i<n; i++){
        z[i].first = arr[i];
        z[i].second = i;
    }
    qsort(z, n, sizeof(pair), cmpP);
    int counter = 1;
    sol[z[0].second] = 1;
    for(int i=1; i<n; i++){
        if(z[i].first == z[i-1].first)
            sol[z[i].second] = counter;
        else{
            counter++;
            sol[z[i].second] = counter;
        }
    }
   *rsz = n;
    return sol;
}
