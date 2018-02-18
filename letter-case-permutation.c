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
/////////////////
void dfs(char*s, int pos, vecs*a){
    if(pos == strlen(s)){
        a->ptr = pushbackS(a->ptr, &a->sz, strdup(s));
        return;
    }
    dfs(s, pos+1, a);
    if(s[pos] >= 'A' && s[pos] <= 'Z' || s[pos] >= 'a' && s[pos] <= 'z'){
        s[pos] ^= 32;
        dfs(s, pos+1, a);
    }
}
char**letterCasePermutation(char*S, int*rsz){
    vecs a = newVecS();
    dfs(S, 0, &a);
   *rsz =  a.sz;
    return a.ptr;
}
