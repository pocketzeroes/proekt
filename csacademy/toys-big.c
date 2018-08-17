#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
////////////////////
vec ans;

void go(int x, int l, int sum){
  ans.ptr = pushback(ans.ptr, &ans.sz, sum + x - 1);
  for (int i = l; i * i <= x; i++){
    if (x % i == 0)
      go(x / i, i, sum + i - 1);
  }
}
int main(){
  int n;
  scanf("%d", &n);
  go(n, 2, 0);
  qsort(ans.ptr, ans.sz, sizeof(int), cmp);
  int asz = unique(ans.ptr, ans.sz);
  printf("%d\n", asz);
  for(int i=0; i<asz; i++){
    printf("%d ", ans.ptr[i]);
  }
}
