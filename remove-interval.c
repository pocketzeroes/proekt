#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

int*newpair(int a, int b){
  int*rez = calloc(2, sizeof(int));
  rez[0] = a;
  rez[1] = b;
  return rez;
}
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int**pushbackP(int**array, int*size, int*value){
  int**output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int**ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef int* pair;
int cmpP(const void*pa, const void*pb){
  pair*aa = (pair*)pa;
  pair*bb = (pair*)pb;
  pair a = *aa;
  pair b = *bb;
  if(a[0] != b[0])return(a[0] < b[0])?-1:1;
  if(a[1] != b[1])return(a[1] < b[1])?-1:1;
  return 0;
}

int**removeInterval(int**intervals, int intervalsSz, int*intervals0sz, int*toBeRemoved, int toBeRemovedSz, int*rsz, int**csz){
  vecp R = newVecP();
  for(int z=0; z<intervalsSz; z++){int*v=intervals[z];
    if(v[1]<=toBeRemoved[0] || toBeRemoved[1]<=v[0])
      pb(R, v);
    else{
      if(v[0]<toBeRemoved[0])
        pb(R, newpair(v[0], toBeRemoved[0]));
      if(toBeRemoved[1]<v[1])
        pb(R, newpair(toBeRemoved[1], v[1]));
    }
  }
  if(R.sz>1)
    qsort(R.ptr, R.sz, sizeof(pair), cmpP);
  int*cols=calloc(R.sz, sizeof(int));
  fill(cols, R.sz, 2);
 *csz=cols;
 *rsz=R.sz;
  return R.ptr;
}
