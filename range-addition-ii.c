int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int maxCount(int m, int n, int** ops, int opsSize, int opsColSize) {
  if(!opsSize){
    return m * n;
  }
  int x = m, y = n;
  for(int i=0; i<opsSize;i++){int*range = ops[i];
    x = min(x, range[0]);
    y = min(y, range[1]);
  }
  return x * y;
}
