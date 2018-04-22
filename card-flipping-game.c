int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
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

int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int flipgame(int*fronts, int frontsSz, int*backs, int backsSz){
  int n = frontsSz;
  vec a = newVec();

  for(int i=0; i<frontsSz; i++) a.ptr=pushback(a.ptr, &a.sz, fronts[i]);
  for(int i=0; i<backsSz ; i++) a.ptr=pushback(a.ptr, &a.sz, backs [i]);

  qsort(a.ptr, a.sz, sizeof(int), cmp);
  int asz = unique(a.ptr, a.sz);
  a.sz = asz;
  for(int z=0; z<a.sz; z++){int x = a.ptr[z];
    char ok = 1;
    for(int i = (0); i < (n); i++)
      if (fronts[i] == x && backs[i] == x) {
        ok = 0;
        break;
      }
    if (ok){
      free(a.ptr);
      return x;
    }
  }
  free(a.ptr);
  return 0;
}
