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

char**findOcurrences(char*text, char*first, char*second, int*rsz){
    vecs sb = newVecS();
    bool fs = true, sec = true;
    char delim[] = " ";
    char*s = strtok(text, delim);
    while(s != NULL){
        if(!sec && !fs){
            fs = true;
            sec = true;
            sb.ptr = pushbackS(sb.ptr, &sb.sz, strdup(s));
        }
        if(strcmp(s, first)==0){
            fs = false;
            goto cont;
        }
        if(strcmp(s, second)==0 && !fs && sec){
            sec = false;
            goto cont;
        }
        else
            fs = sec = true;
 cont:
        s = strtok(NULL, delim);
    }
   *rsz =  sb.sz;
    return sb.ptr;
}
