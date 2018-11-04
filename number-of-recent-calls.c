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

typedef struct {
}RecentCounter;
RecentCounter*gptr;
vec a;
int h;

RecentCounter*recentCounterCreate(){
    a.sz=0;
    h=0;
    return gptr;
}
int recentCounterPing(RecentCounter*obj, int t){
    a.ptr = pushback(a.ptr, &a.sz, t);
    while((h<a.sz)&&(a.ptr[h]+3000<t))
        h++;
    return a.sz-h;
}
void recentCounterFree(RecentCounter*obj){
;
}
