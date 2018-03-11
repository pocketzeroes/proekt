double a[110][110];

double champagneTower(int poured, int query_row, int query_glass){
  int i,j,k;
  memset(a,0,sizeof(a));
  a[0][0]=poured;
  for (i=0;i<105;i++)
    for (j=0;j<=i;j++){
      if (a[i][j]>1){
        a[i+1][j]+=(a[i][j]-1)/2;
        a[i+1][j+1]+=(a[i][j]-1)/2;
        a[i][j]=1;
      }
    }
  return a[query_row][query_glass];
}
