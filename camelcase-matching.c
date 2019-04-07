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

bool go(char*q, char*p){
    int pos = 0;
    int psize=strlen(p);
    for(int i=0;q[i];i++){char c = q[i];
        if(pos<psize && c == p[pos])
            ++pos;
        else if(c < 'a' || c > 'z')
            return false;
    }
    return pos == psize;
}
bool*camelMatch(char**queries, int queriesSz, char*pattern, int*rsz){
    vecb ans = newVecB();
    for(int z=0;z<queriesSz;z++){char* q = queries[z];
        ans.ptr = pushbackB(ans.ptr, &ans.sz, go(q, pattern));
    }
   *rsz = ans.sz;
    return ans.ptr;
}
