#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int p[3000];
int*findRedundantConnection(int**edges, int edgesSz, int edges0sz, int*rsz){
  int i,j,k,n,x,y,tmp;
  vec ans = newVec();
  n = edgesSz;
  for (i=0;i<3000;i++)
    p[i]=i;
  for (i=0;i<n;i++){
    x=edges[i][0];
    y=edges[i][1];
    if (p[x]==p[y]){
     *rsz = edges0sz;
      return edges[i];
    }
    tmp=p[y];
    for (j=0;j<3000;j++)
      if (p[j]==tmp)
        p[j]=p[x];
  }
 *rsz =  ans.sz;
  return ans.ptr;
}
