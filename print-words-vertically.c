int vasprintf(char **str, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;
  __builtin_va_copy(tmpa, args);
  size = vsnprintf(NULL, size, fmt, tmpa);
  __builtin_va_end(tmpa);
  if (size < 0) { return -1; }
  *str = (char *)malloc(size + 1);
  if (NULL == *str) { return -1; }
  size = vsprintf(*str, fmt, args);
  return size;
}
int asprintf(char **str, const char *fmt, ...) {
  int size = 0;
  va_list args;
  __builtin_va_start(args, fmt);
  size = vasprintf(str, fmt, args);
  __builtin_va_end(args);
  return size;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
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
char buff[100000];
vecs split(char*s){
  vecs rez=newVecS();
  while(1){
    sscanf(s, "%s", &buff);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(buff));
    s = strchr(s, ' ');
    if(s==NULL)break;
    s++;
  }
  return rez;
}
///////////////////////////
char**printVertically(char*s, int*rsz){
    vecs v = split(s);
    int n = v.sz;
    vecs w = newVecS();
    for(int i=0; i<n; ++i){
        for(int j=0; v.ptr[i][j]; ++j){
            while(j >= w.sz)
               pbs(w, strdup(""));
            for(int k=0; k<i; ++k)
                if(k >= strlen(w.ptr[j]))
                    w.ptr[j] = concatc(w.ptr[j], ' ');
            w.ptr[j] = concatc(w.ptr[j], v.ptr[i][j]);
        }
    }
   *rsz=   w.sz;
    return w.ptr;
}
