#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int upper_bound(pair*a, int n, pair x){
  int l = 0;
  int h = n;
  while(l < h){
    int mid = (l + h) / 2;
    if(cmpP(&x, &a[mid])>=0)
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}

///////////////////////////////////////

int main(){
  int n, k;
  scanf("%d %d", &n, &k);
  ++n;
  int h[n];
  for(int i=0; i<n; ++i)
    scanf("%d", &h[i]);
  int shifted[n];
  for(int j=0; j<k; ++j){
    double q;
    scanf("%lf", &q);
    int r = (int)(round(q * 10));
    for(int i=0; i<n; ++i)
      shifted[i] = h[i]-i*r;
    vecp down = newVecP();
    pbp(down, newpair(shifted[0], 0));
    for(int i=1; i<n; ++i)
      if(down.ptr[down.sz-1].first > shifted[i])
        pbp(down, newpair(shifted[i], i));
    reverse(down.ptr, 0, down.sz-1);
    double longest = 0;
    for(int i=0; i<n; ++i){
      int pos = upper_bound(down.ptr, down.sz, newpair(shifted[i], n));
      --pos;
      int end = down.ptr[pos].second;
      longest = fmax(longest, (double)(i - end));
      int capacity = shifted[i] - down.ptr[pos].first;
      if(end > 0){
        double diff = shifted[end - 1] - shifted[end];
        longest = fmax(longest, i - end + fmin(1.0, capacity / diff));
      }
      if(i + 1 < n && shifted[i + 1] != shifted[i]){
        double diff = shifted[i] - shifted[i + 1];
        longest = fmax(longest, i - end + fmin(1.0, capacity / diff));
      }
    }
    if(longest<1e-6)
      puts("impossible");
    else
      printf("%.9lf\n", longest);
  }
  return 0;
}
