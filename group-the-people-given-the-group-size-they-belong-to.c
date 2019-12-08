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
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
vec v[505];

int**groupThePeople(int*a, int aSz, int*rsz, int**csz){
  int*cols = calloc(500, sizeof(int));
  int**ans = newmat(500, 500);
  int ansSz=0;
  for(int i=0; i<aSz; ++i){
    pb(v[a[i]], i);
    if(v[a[i]].sz == a[i]){
    #define v2 v[a[i]]
      for(int z=0;z<v2.sz;z++)
        ans[ansSz][z] = v2.ptr[z];
      cols[ansSz]=v2.sz;
#undef v2
      ansSz++;
      v[a[i]].sz=0;
    }
  }
 *csz = cols;
 *rsz = ansSz;
  return ans;
}
