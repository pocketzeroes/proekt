#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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

enum{ MAXN = 1 << 17};
int n;
char polje[10][MAXN];
vec V;

bool dfs(int x, int y){
  if(polje[x][y] == 'X')
    return 0;
  if(y == n-1)
    return 1;
  polje[x][y] = 'X';
  if(dfs(fmin(9, x+1), y+1))
    return 1;
  if(dfs(fmax(0, x-1), y+1)){
    pb(V, y);
    return 1;
  }
  return 0;
}
int main(){
  scanf("%d", &n);
  for(int i=0; i<10; ++i)
    scanf("%s", &polje[i]);
  dfs(9, 0);
  reverse(V.ptr, 0, V.sz-1);
  printf("%d\n", V.sz);
  for(int i=0;i<V.sz;i++)
    printf("%d 1\n", V.ptr[i]);
  return 0;
}
