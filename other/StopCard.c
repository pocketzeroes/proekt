#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

int main(){
  int n, c;
  scanf("%d %d", &n, &c);
  vec adam = newVec();
  int sum = 0;
  for(int i = 0; i < n; i++){
    int val;
    scanf("%d", &val);
    sum += val;
    adam.ptr = pushback(adam.ptr, &adam.sz, val);
  }
  if(n == 1){
    printf("%d\n", adam.ptr[0]);
    return 0;
  }
  else if (c == 0){
    printf("%lf\n", sum/(double)n);
    return 0;
  }
  qsort(adam.ptr, adam.sz, sizeof(int), cmp);
  sum -= adam.ptr[n-1];
  double ev = 0;
  double prob = 1;
  double chance = c/(double)n;
  ev += chance*(sum/(double)(n-1));
  prob -= chance;
  int backsum = adam.ptr[n-1];
  int curr = n - 1;
  for(int i = n - 2; i >= 0 && curr >= c; i--){
    chance = c/(double)curr;
    double factor = chance*prob;
    ev += factor*(backsum/(double)(n-i-1));
    backsum += adam.ptr[i];
    curr--;
    prob -= factor;
  }
  printf("%.8f\n", ev);
  return 0;
}
