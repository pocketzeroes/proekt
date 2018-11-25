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
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
////////////////
bool validateStackSequences(int*pushed, int pushedSz, int*popped, int poppedSz){
  reverse(popped, 0, poppedSz-1);
  vec stk = newVec();
  for(int i=0; i<pushedSz; i++){
    stk.ptr = pushback(stk.ptr, &stk.sz, pushed[i]);
    while(stk.sz && poppedSz && stk.ptr[stk.sz-1] == popped[poppedSz-1]){
      stk.sz--;
      poppedSz--;
    }
  }
  if(poppedSz)
    return false;
  return true;
}
