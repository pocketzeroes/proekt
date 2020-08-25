int*d;
int N;
int M;
void mmalloc(const int n, const int fg){
  d = (int*)malloc(n*sizeof(int));
  M = n;
  if(fg)
    init(n);
}
void ffree(void){
  free(d);
}
void init(const int n){
  int i;
  N = n;
  for(i=0; i<n; i++)
    d[i] = -1;
}
int get(int a){
  int t = a;
  int k;
  while(d[t]>=0)
    t=d[t];
  while(d[a]>=0){
    k=d[a];
    d[a]=t;
    a=k;
  }
  return a;
}
int connect(int a, int b){
  if(d[a]>=0)
    a=get(a);
  if(d[b]>=0)
    b=get(b);
  if(a==b)
    return 0;
  if(d[a] < d[b]){
    d[a] += d[b];
    d[b] = a;
  }
  else{
    d[b] += d[a];
    d[a] = b;
  }
  return 1;
}

bool containsCycle(char**grid, int gridSz, int*grid0sz){
  int i;
  int X = gridSz;
  int Y = grid0sz[0];
  int dm = Y;
  mmalloc(X*Y, 1);
  int dmo(int a, int b){
    return a * dm + b;
  }
  for(i=0; i<X; i++){
    int j;
    for(j=0; j<Y; j++){
      if(i+1 < X && grid[i][j]==grid[i+1][j]){
        if(!connect(dmo(i,j), dmo(i+1, j))){
          ffree();
          return true;
        }
      }
      if(j+1 < Y && grid[i][j]==grid[i][j+1]){
        if(!connect(dmo(i,j), dmo(i, j+1))){
          ffree();
          return true;
        }
      }
    }
  }
  ffree();
  return false;
}
