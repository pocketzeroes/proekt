#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
////////////////////////
typedef struct {
}CustomStack;
CustomStack*gptr;

int maxSize;
vec stack;

CustomStack*customStackCreate(int mxSize){
    maxSize = mxSize;
    stack = newVec();
    return gptr;
}
void customStackPush(CustomStack* obj, int x) {
    if(stack.sz < maxSize)
       pb(stack, x);
}
int customStackPop(CustomStack* obj) {
    if(stack.sz==0)
        return -1;
    int x = stack.ptr[stack.sz-1];
    stack.sz--;
    return x;
}
void customStackIncrement(CustomStack* obj, int k, int val) {
    for(int i=0; i<fmin(k, stack.sz); i++)
        stack.ptr[i] += val;
}
void customStackFree(CustomStack* obj) {
    ;
}
