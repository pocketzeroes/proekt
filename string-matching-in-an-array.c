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
///////////////////////////////
bool isSub(char*a, char*b){
    int a_size = strlen(a);
    int b_size = strlen(b);
    if(a_size > b_size)
        return false;
    int as = a_size,
        bs = b_size;
    for(int i=0; i<=bs-as; ++i){
        bool ok = true;
        for(int j=0; j<as; ++j){
            if(a[j]!=b[i + j]){
                ok = false;
                break;
            }
        }
        if(ok)
            return true;
    }
    return false;
}
char**stringMatching(char**words, int wordsSz, int*rsz){
    vecs ans = newVecS();
    for(int z=0;z<wordsSz;z++){char*str = words[z];
        bool ok = false;
        for(int q=0; q<wordsSz; q++){char*ss = words[q];
            if(strcmp(str, ss)!=0 && isSub(str, ss)){
                ok = true;
                break;
            }
        }
        if(ok)
           pbs(ans, strdup(str));
    }
   *rsz =  ans.sz;
    return ans.ptr;
}
