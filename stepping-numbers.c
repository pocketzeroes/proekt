int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
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
typedef long long ll;
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


vecl V[11];

int*countSteppingNumbers(int low, int high, int*rsz){
    int i;
    if(V[0].sz==0){
        pbl(V[0], 0);
        for(i=1;i<=9;i++) 
            pbl(V[1], i);
        for(i=2;i<=10;i++) {
            for(int z=0;z<V[i-1].sz;z++){ll v=V[i-1].ptr[z];
                int d=v%10;
                if(d>0)
                    pbl(V[i], v*10+(d-1));
                if(d<9)
                    pbl(V[i], v*10+(d+1));
            }
        }
    }
    vec R=newVec();
    for(i=0;i<11;i++)
        for(int z=0;z<V[i].sz;z++){ll v = V[i].ptr[z];
            if(v>=low && v<=high)
                pb(R, v);
        }
    if(R.ptr!=NULL)
      if(R.sz>1)
        qsort(R.ptr, R.sz, sizeof(int), cmp);
   *rsz=   R.sz;
    return R.ptr;
}
