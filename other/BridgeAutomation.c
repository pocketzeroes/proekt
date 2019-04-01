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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
/////////////////
enum{ INF_COST = 1000000};


int solve(vec*boats){
  int n = boats->sz;
  int tbl[n+1];
  fill(tbl, n+1, INF_COST);
  tbl[0] = 0;
  for(int i = 0; i < n; i++){
    int t = boats->ptr[i] + 1800;
    int c = tbl[i] + 120;
    for(int k = i; k < n; k++){
      if(boats->ptr[k] <= t){
        c += 20;
        t += 20;
      }
      else{
        c += boats->ptr[k] - t + 20;
        t  = boats->ptr[k] + 20;
      }
      tbl[k+1] = min(tbl[k+1], c);
    }
  }
  return tbl[n];
}
int main(){
  int nboat;
  scanf("%d", &nboat);
  assert(nboat >= 1 && nboat <= 4000);
  vec boats = newVec();
  for(int i = 0; i < nboat; i++){
    int t;
    int r = scanf("%d", &t);
    boats.ptr = pushback(boats.ptr, &boats.sz, t);
  }
  int ans = solve(&boats);
  printf("%d\n", ans);
  return 0;
}
