int d[60000][2];

int maxProfit(int*a, int aSz, int fee){
  int i, j, k, n;
  n = aSz;
  d[0][0]=0;
  d[0][1]=-fee;
  for(i=0;i+1<n;i++){
    d[i+1][0]=d[i][0];
    if(d[i][1]+a[i+1]-a[i]>d[i+1][0])
      d[i+1][0]=d[i][1]+a[i+1]-a[i];
    d[i+1][1]=d[i][0]-fee;
    if(d[i][1]+a[i+1]-a[i]>d[i+1][1])
      d[i+1][1]=d[i][1]+a[i+1]-a[i];
  }
  return d[n-1][0];
}
