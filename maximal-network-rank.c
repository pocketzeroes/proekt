int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

int mat[100][100];
int sm[100];

int maximalNetworkRank(int n, int**roads, int roadsSz, int*roads0sz){
  int i;
  int res = 0;
  for(i=0; i<n; i++){
    sm[i] = 0;
  }
  for(i=0; i<n; i++){
    int j;
    for(j=0; j<n; j++){
      mat[i][j] = 0;
    }
  }
  for(int z=0;z<roadsSz;z++){int*e = roads[z];
    mat[e[0]][e[1]] = 1;
    mat[e[1]][e[0]] = 1;
  }
  for(i=0; i<n; i++){
    int j;
    for(j=0; j<n; j++){
      sm[i] += mat[i][j];
    }
  }
  for(i=0; i<n; i++){
    int j;
    for(j=i+1; j<n; j++){
      chmax(&res, sm[i] + sm[j] - mat[i][j]);
    }
  }
  return res;
}
