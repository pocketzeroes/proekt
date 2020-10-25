int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}
#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)

bool*checkArithmeticSubarrays(int*nums, int numsSz, int*l, int lSz, int*r, int rSz, int*rsz){
    int m = lSz;
    bool*ans=calloc(m,sizeof(bool));
    REP(i, m){
        bool yes;
        if(r[i] - l[i] + 1 <= 2){
          yes = true;
        }
        else{
          int tmpSz = r[i]+1-l[i];
          int tmp[tmpSz];
          for(int z=0; z<tmpSz; z++){
            tmp[z] = (nums+l[i])[z];
          }
          qsort(tmp, tmpSz, sizeof(int), cmp);
          yes = true;
          int d = tmp[1] - tmp[0];
          REP(j, tmpSz - 1u) {
            if(tmp[j+1] - tmp[j] != d){
              yes = false;
              break;
            }
          }
        }
        ans[i] = yes;
    }
   *rsz=m;
    return ans;
}
