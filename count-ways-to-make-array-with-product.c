enum{nax = 10123};
int C[nax][15];

int*waysToFillArray(int**queries, int queriesSz, int*queries0sz, int*rsz){
  enum{mod = 1000000007};
  if(C[1][1] == 0){
    for(int i = 0; i < nax; ++i){
      C[i][0] = 1;
      if(i < 15){
        C[i][i] = 1;
      }
      for(int j = 1; j < i && j < 15; ++j){
        C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
      }
    }
  }
  int*answer=calloc(queriesSz, sizeof(int));
  for(int z=0;z<queriesSz;z++){int*query = queries[z];
    int n = query[0];
    int k = query[1];
    int total = 1;
    void consider(int cnt){
      total = (long long) total * C[n+cnt-1][cnt] % mod;
    }
    for(int i = 2; i * i <= k; ++i){
      if(k % i == 0){
        int cnt = 0;
        while(k % i == 0){
          k /= i;
          cnt++;
        }
        consider(cnt);
      }
    }
    if(k != 1)
      consider(1);
    answer[z]=total;
  }
 *rsz=queriesSz;
  return answer;
}
