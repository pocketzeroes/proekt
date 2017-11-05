char*concat(char*a, char b){
  char*ptr=NULL;
  if(a==NULL)
      a = strdup("");
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
typedef char* str;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
str*pushback(str*array, int*size, str value){
    str*output = resizeArray(array, str, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    str*ptr;
    int sz;
}vec;
vec newVec(){
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

str*removeComments(str*source, int sourceSz, int*rsz){
    vec ret = newVec();
    char*cur = NULL;
    int f1 = 0, f2 = 0;
    for(int z=0;z<sourceSz;z++){char*src = source[z];
        f1 = 0;
        int srcSz=strlen(src);
        for (int i = 0; src[i]; i++){
            if (f1) 
                break;
            if (f2){
                if (src[i] == '*'){
                    if (i + 1 < srcSz && src[i+1] == '/') {
                        f2 = 0; 
                        i++;
                    }
                }
                continue;
            }
            if (src[i] == '/' && i + 1 < srcSz){
                if (src[i+1] == '/'){f1 = 1; i++; continue;}
                if (src[i+1] == '*'){f2 = 1; i++; continue;}
            }
            cur = concat(cur, src[i]);
        }
        if (!f1 && !f2){
            if (cur != NULL) 
                ret.ptr = pushback(ret.ptr, &ret.sz, cur); 
            cur = NULL;
        }
        if (f1 && cur != NULL){
            ret.ptr = pushback(ret.ptr, &ret.sz, cur);
            cur = NULL;
        }
    }
   *rsz =  ret.sz;
    return ret.ptr;
}





