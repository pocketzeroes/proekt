int D[505050][3];

int*shortestDistanceColor(int*colors, int colorsSz, int**queries, int queriesSz, int*queries0sz, int*rsz){
  int pre[3]={-100000000,-100000000,-100000000};
  int i,j;
  for(i=0;i<colorsSz;i++){
    pre[colors[i]-1]=i;
    for(j=0;j<3;j++)
      D[i][j]=i-pre[j];
  }
  for(j=0;j<3;j++)
    pre[j]=100000000;
  for(i=colorsSz-1;i>=0;i--){
    pre[colors[i]-1]=i;
    for(j=0;j<3;j++)
      D[i][j]=fmin(D[i][j],pre[j]-i);
  }
  int*R=calloc(queriesSz, sizeof(int));
  for(int z=0;z<queriesSz;z++){int*q=queries[z];
    int ret=D[q[0]][q[1]-1];
    if(ret>1<<20)
      ret=-1;
    R[z]=ret;
  }
 *rsz=queriesSz;
  return R;
}
