#define MOD 1000000007
typedef struct{
  int first, second, third;
}trip;
trip newtrip(int a, int b, int c){
  return(trip){a,b,c};
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
//////////////////////////////

vect v;
int ncr[1005][1005];
long long ans;

void add(int a, int b){
    if(a < v.ptr[b].first) {
        if(v.ptr[b].second != -1)
            add(a, v.ptr[b].second);
        else{
            v.ptr[b].second = v.sz;
            pbt(v, newtrip(a, -1, -1));
        }
    }
    else{
        if(v.ptr[b].third != -1)
            add(a, v.ptr[b].third);
        else{
            v.ptr[b].third = v.sz;
            pbt(v, newtrip(a, -1, -1));
        }
    }
}
void ad(int*a){
    if(*a >= MOD)
      (*a)-= MOD;
}
int dfs(int a){
    if(a == -1)
        return 0;
    int ta = dfs(v.ptr[a].second);
    int tb = dfs(v.ptr[a].third);
    ans = ans * ncr[ta + tb][ta] % MOD;
    return ta + tb + 1;
}
int numOfWays(int*nums, int numsSz){
    for(int i=0; i<1005; i++){
        ncr[i][0] = ncr[i][i] = 1;
        for(int j=1; j<i; j++){
            ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
            ad(&ncr[i][j]);
        }
    }
    v=newVecT();
    for(int z=0;z<numsSz;z++){int i = nums[z];
        if(v.sz==0)
           pbt(v, newtrip(i, -1, -1));
        else
            add(i, 0);
    }
    ans = 1;
    dfs(0);
    return(ans + MOD - 1) % MOD;
}
