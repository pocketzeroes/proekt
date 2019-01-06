int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int cmp(const void * a, const void * b){
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
typedef long long ll;


int*powerfulIntegers(int x, int y, int bound, int*rsz){
  vec ret = newVec();
  if(bound<=1){
    *rsz=0;
    return ret.ptr;
  }
  ll xx = 1;
  for(int i=0, i_len=(30); i<i_len; ++i){
    ll yy = 1;
    for(int j=0, j_len=(30); j<j_len; ++j){
      if(xx + yy <= bound)
        ret.ptr = pushback(ret.ptr, &ret.sz, xx + yy);
      yy *= y;
      if(y == 1 || xx + yy > bound)
        break;
    }
    xx *= x;
    if(x == 1 || xx > bound)
      break;
  }
  qsort(ret.ptr, ret.sz, sizeof(int), cmp);
  ret.sz = unique(ret.ptr, ret.sz);
 *rsz=   ret.sz;
  return ret.ptr;
}
