int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
int cmp(const void * a, const void * b){
   return ( *(char*)a - *(char*)b );
}
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

char*orderlyQueue(char*S, int K){
    if(K == 1){
        vecs v=newVecS();
        v.ptr = pushbackS(v.ptr, &v.sz, S);
        for(int i=1; S[i]; ++i){
            char*sub1 = strdup(S+i);
            char*sub2 = strdup(S); sub2[i]='\0';
            char*t = NULL;
            asprintf(&t, "%s%s", sub1, sub2);
            free(sub1);
            free(sub2);
            v.ptr = pushbackS(v.ptr, &v.sz, t);
        }
        qsort(v.ptr, v.sz, sizeof(char*), cmpstr);
        S = v.ptr[0];
    }
    else{
        qsort(S, strlen(S), sizeof(char), cmp);
    }
    return S;
}
