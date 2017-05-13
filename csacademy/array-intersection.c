#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;

void swap(ll*nums, int i, int j) {
   ll  t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll *pushback(ll *array, int *size, ll value) {
    ll *output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	ll*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#define SIZE 100005
vec result;

vec hash_map[SIZE];
void insert(ll element){
  int line = llabs(element) % SIZE;
  hash_map[line].ptr=pushback(hash_map[line].ptr, &hash_map[line].sz,element);
}
void do_remove(ll element){
  int line = llabs(element) % SIZE;
  for (size_t i = 0; i < hash_map[line].sz; i++) {
    if (element == hash_map[line].ptr[i]) {
      result.ptr=pushback(result.ptr, &result.sz, element);
      swap(hash_map[line].ptr, i, hash_map[line].sz-1);
      hash_map[line].sz--;
      break;
    }
  }
}

int n, m;

int main(){
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i += 1) {
    long long element;
    scanf("%lld", &element);
    insert(element);
  }
  for (int i = 0; i < m; i += 1) {
    long long element;
    scanf("%lld", &element);
    do_remove(element);
  }
  printf("%d\n", result.sz);
  for(int i=0;i<result.sz;i++){
    printf("%d ", result.ptr[i]);
  }
  puts("");
}




