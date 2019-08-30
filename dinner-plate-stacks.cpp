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

class DinnerPlates{
  int _capacity;
  vec data[200000]; int data_sz=0;
  int firstNonFullStack;
  int lastNonEmptyStack;
public:
  DinnerPlates(int capacity){
    data_sz=0;
    memset(data, 0, sizeof(data));
    _capacity = capacity;
    firstNonFullStack = 0;
    lastNonEmptyStack = -1;
  }
  void freeVec(vec*v){
    free(v->ptr);
  }
 ~DinnerPlates(){
    for(int i=0;i<data_sz;i++)
      freeVec(&data[i]);
  }
  void push(int val){
    while(firstNonFullStack < data_sz && data[firstNonFullStack].sz >= _capacity)
      ++firstNonFullStack;
    if(firstNonFullStack >= data_sz){
      vec vv=newVec();
      vv.ptr = pushback(vv.ptr, &vv.sz, val);
      data[data_sz++] = vv;
      lastNonEmptyStack = firstNonFullStack;
    }
    else
      data[firstNonFullStack].ptr = pushback(data[firstNonFullStack].ptr, &data[firstNonFullStack].sz, val);
  }
  int pop(){
    while(lastNonEmptyStack >= 0 && data[lastNonEmptyStack].sz==0)
      --lastNonEmptyStack;
    if(lastNonEmptyStack < 0)
      return -1;
    int tmp = data[lastNonEmptyStack].ptr[data[lastNonEmptyStack].sz-1];
    data[lastNonEmptyStack].sz--;
    return tmp;
  }
  int popAtStack(int index){
    if(index >= data_sz)
      return -1;
    if(data[index].sz==0)
      return -1;
    int tmp = data[index].ptr[data[index].sz-1];
    data[index].sz--;
    if(index < firstNonFullStack)
      firstNonFullStack = index;
    return tmp;
  }
};

