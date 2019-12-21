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
void reverse(int*nums, int start, int end){
  while(start < end){
    swap(nums, start, end);
    start++;
    end  --;
  }
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
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

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
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
//////////////////////////////

vecp try(int*a, int n, int l, int r){
  int*b=calloc(n, sizeof(int));
  for(int i=0; i<n; i++)
    b[i]=a[i];
  vecp ans = newVecP();
  for(int i=l-1; i>=0; i--){
    if(b[l]<b[r]){
      if(b[i]<b[l]){
        l = i; 
        continue;
      }
      if(b[i]>b[r]){
        pbp(ans, newpair(l, r));
        reverse(b, l, r);
        l = i;
        continue;
      }
      for(int j = l; j <= r; j++){
        if(b[j] > b[i]) {
          if(l != j-1){
            pbp(ans, newpair(l, j-1));
            reverse(b, l, j-1);
          }
          l = i;
          pbp(ans, newpair(l, j-1));
          reverse(b, l, j-1);
          break;
        }
      }
    }
    else{
      if(b[i] > b[l]){
        l = i;
        continue;
      }
      if(b[i] < b[r]){
        pbp(ans, newpair(l, r));
        reverse(b, l, r);
        l = i;
        continue;
      }
      for(int j = l; j <= r; j++){
        if(b[j] < b[i]){
          if(l != j-1){
            pbp(ans, newpair(l, j-1));
            reverse(b, l, j-1);
          }
          l = i;
          pbp(ans, newpair(l, j-1));
          reverse(b, l, j-1);
          break;
        }
      }
    }
  }
  for(int i = r+1; i < n; i++){
    if(b[l] < b[r]){
      if(b[i] > b[r]){
        r = i; 
        continue;
      }
      if(b[i] < b[l]){
        pbp(ans, newpair(l, r));
        reverse(b, l, r);
        r = i;
        continue;
      }
      for(int j = r; j >= l; j--){
        if(b[j] < b[i]){
          j++;
          if(j != r){
            pbp(ans, newpair(j, r));
            reverse(b, j, r);
          }
          r = i;
          pbp(ans, newpair(j, r));
          reverse(b, j, r);
          break;
        }
      }
    }
    else{
      if(b[i] < b[r]){
        r = i; 
        continue;
      }
      if(b[i] > b[l]){
        pbp(ans, newpair(l, r));
        reverse(b, l, r);
        r = i;
        continue;
      }
      for(int j = r; j >= l; j--){
        if(b[j] > b[i]){
          j++;
          if(j != r){
            pbp(ans, newpair(j, r));
            reverse(b, j, r);
          }
          r = i;
          pbp(ans, newpair(j, r));
          reverse(b, j, r);
          break;
        }
      }
    }
  }
  if(b[0] > b[n-1])
    pbp(ans, newpair(0, n-1));
  return ans;
}
int main(){
  int n;
  scanf("%d", &n);
  int a[n];
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  if(n == 1){
    puts("0");
    return 0;
  }
  for(int i=1; i<n; i++){
    vecp ops = try(a, n, i-1, i);
    if(ops.sz <= 191){
      printf("%d\n", ops.sz);
      for(int z=0;z<ops.sz;z++){pair u = ops.ptr[z];
        printf("%d %d\n", u.first+1, u.second+1);
      }
      return 0;
    }
  }
  return 1;
}
