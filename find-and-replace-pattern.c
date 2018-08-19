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

char**findAndReplacePattern(char**words, int wordsSz, char*pattern, int*rsz){
    vecs ret = newVecS();
    for(int z=0;z<wordsSz;z++){
        char*w = words[z];
        int wlen = strlen(w);
        for(int i=0; i<wlen; i++){
            for(int j=i+1; j<wlen; j++){
                char ii = w[i];
                char jj = w[j];
                char pi = pattern[i];
                char pj = pattern[j];
                if(ii == jj){
                    if(pi != pj)
                        goto outer;
                }
                else if(pi == pj)
                    goto outer;
            }
        }
        ret.ptr = pushbackS(ret.ptr, &ret.sz, w);
      outer:;
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
