#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
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
int used[60][60];

int largestIsland(int**grid, int gridSz, int*gsz){
  int i,j,k,m,n,ans,x,y,xx,yy,l;
  vecp q = newVecP();
  m=gridSz;
  n=gsz[0];
  ans=0;
  for (i=0;i<m;i++)
    for (j=0;j<n;j++)
      if (grid[i][j]==0){
        q.sz=0;
        q.ptr = pushbackP(q.ptr, &q.sz, newPair(i,j));
        memset(used, 0, sizeof(used));
        used[i][j]=1;
        for (k=0;k<q.sz;k++){
          x=q.ptr[k].first;
          y=q.ptr[k].second;
          for (l=0;l<4;l++){
            xx=x+neigh[l][0];
            yy=y+neigh[l][1];
            if ((xx>=0)&&(xx<m)&&(yy>=0)&&(yy<n)&&(used[xx][yy]==0)&&(grid[xx][yy]==1)){
              q.ptr=pushbackP(q.ptr, &q.sz, newPair(xx,yy));
              used[xx][yy]=1;
            }
          }
        }
        if (q.sz>ans) 
          ans=q.sz;
      }
  if (ans==0) 
    ans=m*n;
  return ans;
}
