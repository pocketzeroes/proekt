#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


vec*adj;
int*v;
int n;

int dfs(int p, int*s){
  int i, j, k, ss = v[p], ct = 1, sv, c;
  *s = 0;
  for(int z=0;z<adj[p].sz;z++){int pp = adj[p].ptr[z];
    sv = 0;
    c = dfs(pp, &sv);
    if(sv == 0)
      continue;
    ct += c;
    ss += sv;
  }
  *s = ss;
  if(ss == 0)
    return 0;
  else
    return ct;
}
int deleteTreeNodes(int nodes, int*parent, int parentSz, int*value, int valueSz){
  v = value;
  n = nodes;
  if(adj)free(adj);
  adj = calloc(nodes, sizeof(vec));
  for(int i=0; i<n; i++){
    if(parent[i] != -1)
      pb(adj[parent[i]], i);
  }
  int s;
  int ans = dfs(0, &s);
  return ans;
}
