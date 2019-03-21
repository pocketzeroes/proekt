#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
typedef uint32_t u32;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
u32*pushback(u32*array, int*size, u32 value){
  u32*output = resizeArray(array, u32, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  u32*ptr;
  int sz;
}vec;
vec newVec(){
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
////////////////////

int N, M;
enum{ size = 1<<16};
enum{ mask = size-1};
int *sent, *recv;
u32  count[size] ;
vec bucket[size];

int*read(int l){
  int*t = calloc(l, sizeof(int));
  for(int i=0; i<l; i++)
    scanf("%d", t+i);
  return t;
}
int main(){
  scanf("%d %d", &N, &M);
  sent = read(N);
  recv = read(M);
  for(int i = 0; i < M; i++)
    for(int j = 0 ; j < N  && sent[j]<=recv[i]; j++){
      u32 m = recv[i]-sent[j];
      bucket[m>>16].ptr = pushback(bucket[m>>16].ptr, &bucket[m>>16].sz, m&mask);
    }
  u32 max = 0, maxi = 0 ;
  for(size_t b = 0; b<size; b++){
    for(int z=0; z<bucket[b].sz; z++){u32 cur = bucket[b].ptr[z];
#define c count[cur]
      ++c;
      if(c>=max){
        u32 new_best=(b<<16) + cur;
        if(maxi>new_best || c>max)
          maxi = new_best ;
        max = c;
      }
    }
#undef c
    for(int z=0;z<bucket[b].sz;z++){u32 cur = bucket[b].ptr[z];
      count[cur] = 0;
    }
  }
  printf("%d\n", maxi);
}
