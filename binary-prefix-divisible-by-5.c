#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
bool*pushbackB(bool*array, int*size, bool value){
  bool*output = resizeArray(array, bool, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  bool*ptr;
  int sz;
}vecb;
vecb newVecB(){
  vecb rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

bool*prefixesDivBy5(int*A, int Asz, int*rsz){
    vecb ret = newVecB();
    int x = 0;
    for(int i=0;i<Asz;i++){int v = A[i];
        x = x * 2 + v;
        x %= 5;
        ret.ptr=pushbackB(ret.ptr, &ret.sz, x==0);
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
