#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;

int**pushback2d(int**array, int*size, int* value){
  int* *output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
////////////-------------------
int**ans;
int  ansSz;
vec   tmp;
int a[20][20];
int n;
int*sizes;

void doit(int x){
  int i;
  if (x==n-1){
    sizes[ansSz] = tmp.sz;
    int*tt=calloc(tmp.sz,sizeof(int));
    memcpy(tt, tmp.ptr, tmp.sz*sizeof(int));
    ans = pushback2d(ans, &ansSz, tt);
    return;
  }
  for(i=0;i<n;i++)
    if(a[x][i]==1){
      tmp.ptr = pushback(tmp.ptr, &tmp.sz, i);
      doit(i);
      tmp.sz--;
    }
}
int**allPathsSourceTarget(int**graph, int graphSz, int*graph0sz, int**outcols, int*rsz){
  sizes=calloc(10000,sizeof(int));
  int i,j;
  n=graphSz;
  memset(a,0,sizeof(a));
  for (i=0;i<n;i++){
    for (j=0;j<graph0sz[i];j++)
      a[i][graph[i][j]]=1;
  }
  ansSz=0;
  tmp.sz=0;
  tmp.ptr = pushback(tmp.ptr, &tmp.sz, 0);
  doit(0);
 *outcols = sizes;
 *rsz=   ansSz;
  return ans;
}
