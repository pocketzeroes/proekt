#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>



#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
  int first;
  int second;
}pair;
typedef double ld;

void swap(pair*nums, int i, int j){
  pair t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(pair*nums, int start, int end){
  while(start < end){
    swap(nums, start, end);
    start++;
    end  --;
  }
}

void swapLD(ld*nums, int i, int j){
  ld t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverseLD(ld*nums, int start, int end){
  while(start < end){
    swapLD(nums, start, end);
    start++;
    end  --;
  }
}




//////////////////
pair v[1000000];
ld phase[2][1000000];

ld angle(int a, int b){
  if(a==-1 || b==-1 || v[b].second<=v[a].second)
    return M_PI/2.;
  return atan2(abs(v[a].first-v[b].first), v[b].second-v[a].second);
}
void solve(int n, ld*res){
  vec all = newVec();
  all.ptr=pushback(all.ptr, &all.sz, -1);
  for(int i=0; i<n; i++){
    while(all.sz>=2 && angle(i, all.ptr[all.sz-2]) <= angle(i, all.ptr[all.sz-1]))
      all.sz--;
    res[i] = angle(i, all.ptr[all.sz-1]);
    all.ptr=pushback(all.ptr, &all.sz, i);
  }
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    scanf("%d %d", &v[i].first, &v[i].second);
  for (int i=2; i--; reverse(v, 0, n-1))
    solve(n, phase[i]);
  reverseLD(phase[0], 0, n-1);
  for(int i=0; i<n; i++)
    printf("%.9lf\n", (phase[0][i]+phase[1][i])*12./M_PI );
  return 0;
}
