void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*upper;
int upperSz;
void newDJSet(int n){
  upperSz = n;
  upper = calloc(n, sizeof(int));
  fill(upper, n, -1);
}
int root(int x){
  return upper[x] < 0 ? x : (upper[x] = root(upper[x]));
}
bool equiv(int x, int y){
  return root(x) == root(y);
}
bool ds_union(int x, int y){
  x = root(x);
  y = root(y);
  if (x != y) {
    if (upper[y] < upper[x]) {
      int d = x;
      x = y;
      y = d;
    }
    upper[x] += upper[y];
    upper[y] = x;
  }
  return x == y;
}
int count(){
  int ct = 0;
  for(int z=0;z<upperSz;z++){int u = upper[z];
    if (u < 0)
      ct++;
  }
  return ct;
}
int regionsBySlashes(char**s, int gridSz){
  int n = gridSz, 
      m = strlen(s[0]);
  newDJSet(n*m*4);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(i+1 < n){
        ds_union((i*m+j)*4+2, ((i+1)*m+j)*4);
      }
      if(j+1 < m){
        ds_union((i*m+j)*4+3, (i*m+j+1)*4+1);
      }
      if(s[i][j] == ' '){
        ds_union((i*m+j)*4+0, (i*m+j)*4+1);
        ds_union((i*m+j)*4+2, (i*m+j)*4+1);
        ds_union((i*m+j)*4+2, (i*m+j)*4+3);
      }
      else if(s[i][j] == '/'){
        ds_union((i*m+j)*4+0, (i*m+j)*4+1);
        ds_union((i*m+j)*4+2, (i*m+j)*4+3);
      }
      else{
        ds_union((i*m+j)*4+0, (i*m+j)*4+3);
        ds_union((i*m+j)*4+2, (i*m+j)*4+1);
      }
    }
  }
  return count();
}
