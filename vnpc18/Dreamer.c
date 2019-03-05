#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j){
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void rev(int*s, int l, int r){
  while(l<r)
    swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
  int index = -1;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(s[mid]<=key)
      r=mid-1;
    else{
      l=mid+1;
      if(index = -1 || s[index]<=s[mid])
        index = mid;
    }
  }
  return index;
}
bool next_permutation(int*s, int sl){
  int len = sl, i=len-2;
  while(i>=0 && s[i]>=s[i+1])
    --i;
  if(i<0)
    return false;
  else{
    int index=b_search(s, i+1, len-1, s[i]);
    swap(s, i, index);
    rev(s, i+1, len-1);
    return true;
  }
}
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
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

char temp[100000];
int tc;
vec v;

bool isValid(vec*k){
  int d = k->ptr[6] * 10+k->ptr[7];
  int m = k->ptr[4] * 10+k->ptr[5];
  int y = k->ptr[0] * 1000 + k->ptr[1]*100 + k->ptr[2] * 10 + k->ptr[3];
  if (d < 1 || d > 31 || m < 1 || m > 12 || y < 2000)
    return false;
  if (d > 29 && m == 2)
    return false;
  if (d == 31)
    if (m == 4 || m == 6 || m == 9 || m == 11)
      return false;
  if (d == 29 && m == 2 && (y%4!=0 || (y%100==0 && y%400!=0)))
    return false;
  return true;
}
int main(){
  scanf("%d", &tc);
  fgets(temp, 1000, stdin);
  for(int i=0; i<tc; i++){
    fgets(temp, 1000, stdin);
    v.sz=0;
    for(int j = 0; temp[j]; j++){
      if('0' <= temp[j] && temp[j] <= '9')
        v.ptr = pushback(v.ptr, &v.sz, temp[j]-'0');
    }
    int res = 0;
    qsort(v.ptr, v.sz, sizeof(int), cmp);
    vec ed = newVec();
    do{
      if(isValid(&v)){
        if(ed.sz == 0){
          ed.sz = v.sz;
          ed.ptr=calloc(v.sz, sizeof(int));
          for(int i=0; i<v.sz; i++)
            ed.ptr[i] = v.ptr[i];
        }
        res++;
      }
    }
    while(next_permutation(v.ptr, v.sz));
    printf("%d", res);
    if(ed.sz != 0){
      printf(" ");
      printf("%d%d ", ed.ptr[6], ed.ptr[7] );
      printf("%d%d ", ed.ptr[4], ed.ptr[5] );
      printf("%d%d%d%d\n", ed.ptr[0], ed.ptr[1], ed.ptr[2], ed.ptr[3]);
    }
    else
      puts("");
  }
  return 0;
}
