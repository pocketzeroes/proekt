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
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

/////////////////
int*advantageCount(int*A, int Asz, int*B, int Bsz, int*rsz){
    vecp gvp = newVecP();
    vec  ans = newVec();
    int n = Bsz;
    for(int i=0; i<n; ++i){
        gvp.ptr = pushbackP(gvp.ptr, &gvp.sz, newPair(B[i],i));
        ans.ptr = pushback(ans.ptr, &ans.sz, -1);
    }
    qsort(gvp.ptr, gvp.sz, sizeof(pair), cmpP);
    qsort(A, Asz, sizeof(int), cmp);
    int p1 = 0,
        p2 = n-1;
    for(int i=n-1; i>=0; --i){
        if(A[p2] > gvp.ptr[i].first)
            ans.ptr[gvp.ptr[i].second] = A[p2--];
        else
            ans.ptr[gvp.ptr[i].second] = A[p1++];
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
