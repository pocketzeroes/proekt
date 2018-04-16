char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
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
/////////////////
vecs F(char*s){
  vecs ret = newVecS();
  int slen=strlen(s);
  if(slen==0)
    return ret;
  if(slen == 1 || s[0] != '0')
    ret.ptr = pushbackS(ret.ptr, &ret.sz, s);
  if(s[slen-1] != '0'){
    int n = slen;
    for(int i=1; i<n; i++){
      if(i == 1 || s[0] != '0'){
//      printf("s=%s i=%d\n", s, i);
        char*kvo=NULL;
        char*lev = substr(s, 0, i);
        char*des = s+i;
//      printf("des=%s\n", des);
        asprintf(&kvo, "%s.%s", lev, des);
        ret.ptr = pushbackS(ret.ptr, &ret.sz, kvo);
      }
    }
  }
  return ret;
}
char**ambiguousCoordinates(char*S, int*rsz){
  vecs ret=newVecS();
  int n = strlen(S);
  for(int i=2; i<n-1; i++){
    vecs left  = F(substr(S, 1, i-1  ));
    vecs right = F(substr(S, i, n-1-i));
    for(int l=0;l<left.sz;l++){char*e=left.ptr[l];
      for(int r=0;r<right.sz;r++){char*f=right.ptr[r];
        char*pb=NULL;
        asprintf(&pb,"(%s, %s)", e, f);
        ret.ptr = pushbackS(ret.ptr, &ret.sz, pb);
      }
    }
  }
 *rsz=   ret.sz;
  return ret.ptr;
}
