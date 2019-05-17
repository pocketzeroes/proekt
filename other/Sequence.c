#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
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
////////////
enum{ MAX_N =    1000000};
enum{ INFTY = 1000000001};
int n, a[MAX_N + 2];
vec stack;

int main(){
  scanf("%d", &n);
  for(int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  a[0] = a[n + 1] = INFTY;
  long long res = 0LL;
  stack.ptr = pushback(stack.ptr, &stack.sz, a[0]);
  for(int i = 1; i <= n + 1; i++){
    while(a[i] >= stack.ptr[stack.sz-1]){
      int change = min(stack.ptr[stack.sz - 2], a[i]);
      if(change == INFTY)
        break;
      res += change;
      stack.sz--;
    }
    stack.ptr = pushback(stack.ptr, &stack.sz, a[i]);
  }
  printf("%lld\n", res);
  return 0;
}
