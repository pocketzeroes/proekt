#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int gcd(int x, int y){
    return y?gcd(y,x%y):x;
}
char*tostr(int v, int w){
  char*ptr=NULL;
  asprintf(&ptr, "%d/%d", v, w);
  return ptr;
}

char**simplifiedFractions(int n, int*rsz){
    vecs ret=newVecS();
    for(int i=1; i<=n; ++i)
        for(int j=i+1; j<=n; ++j)
            if(gcd(i, j)==1){
                char*buf = tostr(i, j);
                pbs(ret, buf);
            }
   *rsz= ret.sz;
    return ret.ptr;
}
