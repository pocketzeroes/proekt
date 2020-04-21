#define back(_v) _v.ptr[_v.sz-1]
typedef long long ll;
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
void swap(ll*nums, ll i, ll j){
  ll t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(ll*nums,ll start,ll end){
  while( start < end) {
    swap(nums, start, end);
    start++;
    end  --;
  }
}

int findMinFibonacciNumbers(int k){
  vecl V = newVecL();
  pbl(V, 1);
  pbl(V, 1);
  int i;
  for(i=0; i<50; i++)
    pbl(V, back(V)+V.ptr[V.sz-2]);
  int ret=0;
  reverse(V.ptr, 0, V.sz-1);
  for(int z=0;z<V.sz;z++){ll v=V.ptr[z];
    while(k>=v)
      k-=v, ret++;
  }
  return ret;
}
