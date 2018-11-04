typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int neigh[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int used[110][110];

int shortestBridge(int**a, int aSz, int*a0sz){
  int i,j,k,m,n,x,y,xx,yy,b1,ans;
  vecp q = newVecP();
  m = aSz;
  n = a0sz[0];
  b1 = 0;
  memset(used, 0, sizeof(used));
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      if(a[i][j]==1){
        used[i][j]=1;
        q.ptr = pushbackP(q.ptr, &q.sz, newPair(i,j));
        b1=1;
        break;
      }
    }
    if (b1==1)
      break;
  }
  for(i=0;i<q.sz;i++){
    x=q.ptr[i].first;
    y=q.ptr[i].second;
    for(j=0;j<4;j++){
      xx=x+neigh[j][0];
      yy=y+neigh[j][1];
      if ((xx>=0)&&(xx<m)&&(yy>=0)&&(yy<n)&&(used[xx][yy]==0)&&(a[xx][yy]==1)){
        q.ptr = pushbackP(q.ptr, &q.sz, newPair(xx,yy));
        used[xx][yy]=1;
      }
    }
  }
  for (i=0;i<q.sz;i++){
    x=q.ptr[i].first;
    y=q.ptr[i].second;
    for (j=0;j<4;j++){
      xx=x+neigh[j][0];
      yy=y+neigh[j][1];
      if ((xx>=0)&&(xx<m)&&(yy>=0)&&(yy<n)&&(used[xx][yy]==0)&&(a[xx][yy]==0)){
        q.ptr = pushbackP(q.ptr, &q.sz, newPair(xx,yy));
        used[xx][yy]=used[x][y]+1;
      }
    }
  }
  ans=2000000000;
  for (i=0;i<m;i++)
    for (j=0;j<n;j++)
      if (used[i][j]==0){
        for (k=0;k<4;k++){
          xx=i+neigh[k][0];
          yy=j+neigh[k][1];
          if ((xx>=0)&&(xx<m)&&(yy>=0)&&(yy<n)&&(used[xx][yy]!=0)&&(a[xx][yy]==0)){
            if (used[xx][yy]<ans)
              ans=used[xx][yy];
          }
        }
      }
  return ans-1;
}
