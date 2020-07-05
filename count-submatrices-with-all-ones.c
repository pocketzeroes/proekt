#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
  
void chmax(int*a, int b){
  if(*a<b)
    *a=b;
}
int numSubmat(int**mat, int matSz, int*mat0sz){
  int h=matSz;
  int w=mat0sz[0];
  int sm[h+1][w+1]; clr(sm);
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      sm[i+1][j+1]=mat[i][j];
  for(int i=0;i<=h;i++)
    for(int j=0;j<w;j++)
      sm[i][j+1]+=sm[i][j];
  for(int i=0;i<h;i++)
    for(int j=0;j<=w;j++)
      sm[i+1][j]+=sm[i][j];
  bool check(int u,int d,int l,int r){
    assert(u<d && l<r);
    int res=(sm[u][l]+sm[d][r])-(sm[d][l]+sm[u][r]);
    return (d-u)*(r-l)==res;
  }
  int ans=0;
  for(int u=0;u<h;u++){
    for(int d=u+1;d<=h;d++){
      int r=0;
      for(int l=0;l<w;l++){
        chmax(&r,l);
        while(r+1<=w && check(u,d,l,r+1))
          r++;
        ans+=r-l;
      }
    }
  }
  return ans;
}
