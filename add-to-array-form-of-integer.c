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

void inc(vec*a){
    int N=a->sz;
    bool st=0;
    for(int i=N-1; i>=0; i--){
        if(a->ptr[i]==9)
           a->ptr[i]= 0;
        else{
            a->ptr[i]++;
            st=1;
            break;
        }
    }
    if(!st){
        a->ptr[0]=1;
        a->ptr = pushback(a->ptr, &a->sz, 0);
    }
}
int*addToArrayForm(int*A, int Asz, int K, int*rsz){
    vec a;
    a.ptr = calloc(Asz, sizeof(int));
    a.sz  = Asz;
    for(int i=0;i<Asz;i++)
        a.ptr[i]=A[i];
    while(K-- > 0)
        inc(&a);
   *rsz=   a.sz;
    return a.ptr;
}
