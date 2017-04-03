#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}

int*p;
int pSz;
int n;
int FIND(int x){
  if(p[x]==x) 
    return p[x];
  else 
    p[x]=FIND(p[x]);
  return p[x];
}
void UNION(int x, int y){
  p[FIND(x)] = FIND(y);
}
int findCircleNum(int** M, int MRowSize, int MColSize){
  p = NULL;pSz=0;
  n = MColSize;
  for(int i=0;i<n;i++) 
    p=pushback(p,&pSz,i);
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++) 
      if(M[i][j]==1) 
        UNION(i, j);
  int cnt=0;
  for(int i=0;i<n;i++)
    if(FIND(i) == i) 
      ++cnt;
  return cnt;
}
