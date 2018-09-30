int max(int a,int b){return a>b?a:b;}
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

char**wordSubsets(char**A, int Asz, char**B, int Bsz, int*rsz){
    int gf[26]={0};
    for(int z=0;z<Bsz;z++){char*b = B[z];
        int f[26]={0};
        for(int i=0;b[i];i++){char c = b[i];
            f[c-'a']++;
        }
        for(int i=0; i<26; i++){
            gf[i] = max(gf[i], f[i]);
        }
    }
    vecs ret = newVecS();
    for(int z=0;z<Asz;z++){char*a = A[z];
        int f[26]={0};
        for(int i=0;a[i];i++){char c = a[i];
            f[c-'a']++;
        }
        for(int i = 0; i < 26; i++){
            if(f[i] < gf[i])
                goto outer;
        }
        ret.ptr = pushbackS(ret.ptr, &ret.sz, a);
  outer:;
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
