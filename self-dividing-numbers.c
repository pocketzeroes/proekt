char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int*selfDividingNumbers(int left, int right, int*rsz){
    vec a = newVec();
    for(int i = left; i <= right; ++i){
        char* s = to_string(i);
        bool ok = true;
        for(int z=0;s[z];z++){ char c = s[z];
            int x = c - '0';
            if (x == 0 || i % x){
                ok = false;
                break;
            }
        }
        if (ok) 
            a.ptr = pushback(a.ptr, &a.sz, i);
    }
   *rsz=   a.sz;
    return a.ptr;
}
