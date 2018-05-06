#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int**pushback2i(int**array, int*size, int*value) {
  int**output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  int**ptr;
  int sz;
}vec2i;
vec2i newVec2i() {
  vec2i rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
//////////////
int**largeGroupPositions(char*S, int**csz, int*rsz){
    int n = strlen(S), i, j;
    vec2i ans = newVec2i();
    int*sizes = calloc(n, sizeof(int));

    for(i=0; i<n; i=j){
        for(j=i; j<n && S[i]==S[j]; j++);
        if(j-i>2){
            int*o = calloc(2, sizeof(int));
            o[0] = i;
            o[1] = j-1;
            ans.ptr = pushback2i(ans.ptr, &ans.sz, o);
        }
    }
    
    for(int i=0; i<ans.sz; i++)
        sizes[i] = 2;
    *csz = sizes;
    *rsz = ans.sz;
    return ans.ptr;
}
