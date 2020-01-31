#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define back(vv) vv.ptr[vv.sz-1]

int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

void swap(int*nums, int i, int j){
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(int*nums, int start, int end){
  while(start < end){
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pb2(zpv, zvv) zpv.ptr = pushback2d(zpv.ptr, &zpv.sz, zvv)
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

///////////////////////////////////-------------------------

vec LIS(int*a, int asz){
  int n = asz;
  if(n == 0)
    return newVec();
  vec   lis     = newVec();
  vec   parent  = newVec();
  vec2d history = newVec2d();
  for(int i=0; i<n; i++){
    int x = a[i];
    int it = lower_bound(lis.ptr, lis.sz, x);
    if(it == lis.sz){
      pb(lis, x);
      int len = history.sz;
      int p = (len == 0) ? -1 : back(history.ptr[len-1]);
      pb(parent, p);
      vec nv=newVec();
      pb(nv, i);
      pb2(history, nv);
    }
    else{
      lis.ptr[it] = x;
      int idx = it;
      int p = (idx == 0) ? -1 : back(history.ptr[idx-1]);
      pb(parent, p);
      pb(history.ptr[it], i);
    }
  }
  vec ret = newVec();
  for(int i=back(back(history)); i!=-1; i=parent.ptr[i])
    pb(ret, i);
  reverse(ret.ptr, 0, ret.sz-1);
  return ret;
}

int main(){
  int n;
  scanf("%d", &n);
  int a[n+2];
  a[0] = 0;
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  a[n+1] = n + 1;
  vec increasing = LIS(a, n+2);
  int b[n+2]; memcpy(b, a, sizeof(b));
  int bsz = n+2;
  reverse(b, 0, bsz-1);
  for(int i=0; i<bsz; i++)
    b[i] *= -1;
  vec decreasing = LIS(b, bsz);
  int r = increasing.sz;
  for(int i=0; i<r; i++)
    increasing.ptr[i] = a[increasing.ptr[i]];
  reverse(decreasing.ptr, 0, decreasing.sz-1);
  for(int i=0; i<r; i++)
    decreasing.ptr[i] = -b[decreasing.ptr[i]];
  vec critical = newVec();
  for(int i=0, j=0; i<r && j<r;){
    if(increasing.ptr[i] == 0 || increasing.ptr[i] == n + 1){
      i++;
      continue;
    }
    if(decreasing.ptr[j] == 0 || decreasing.ptr[j] == n + 1){
      j++;
      continue;
    }
    if(increasing.ptr[i] < decreasing.ptr[j])
      i++;
    else if(increasing.ptr[i] > decreasing.ptr[j])
      j++;
    else{
      pb(critical, increasing.ptr[i]);
      i++, j++;
    }
  }
  if(critical.sz == 0)
    puts("-1");
  else{
    bool space = false;
    for(int z=0;z<critical.sz;z++){int x = critical.ptr[z];
      if(space)
        printf(" ");
      space = true;
      printf("%d", x);
    }
    puts("");
  }
  return 0;
}
