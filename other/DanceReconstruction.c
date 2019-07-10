#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int gcd(int a, int b){
  if (a==0)
    return b;
  return gcd (b%a, a);
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
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
/////////////////////////

int sort_by_size(const void*pa, const void*pb){
  vec*a=(vec*)pa;
  vec*b=(vec*)pb;
  return(a->sz < b->sz)?-1:1;
}
int main(){
  int n,k;
  scanf("%d %d", &n, &k);
  int*p = calloc(n, sizeof(int));
  for(int i=0; i<n; ++i)
    scanf("%d", &p[i]);
  vec2d cycles = newVec2d();
  int*seen = calloc(n, sizeof(int));
  for(int i=0; i<n; ++i){
    if(!seen[i]){
      int j=i;
      vec cycle = newVec();
      while(!seen[j]){
        seen[j]=1;
        cycle.ptr = pushback(cycle.ptr, &cycle.sz, j);
        j=p[j]-1;
      }
      cycles.ptr = pushback2d(cycles.ptr, &cycles.sz, cycle);
    }
  }
  free(seen);
  free(p);
  int*final=calloc(n, sizeof(int));
  int ptr=0;
  qsort(cycles.ptr, cycles.sz, sizeof(vec), sort_by_size);
  while(ptr<cycles.sz){
    int size = cycles.ptr[ptr].sz;
    int needed = size;
    int k2 = k;
    while(k2>1 && gcd(size,k2)!=1){
      needed *= gcd(size,k2);
      k2 /= gcd(size, k2);
    }
    if(ptr+needed/size>n || cycles.ptr[ptr+needed/size-1].sz != size){
      puts("Impossible");
      return 0;
    }
    int*original_cycle=calloc(needed, sizeof(int));
    for(int c=0; c<(needed/size); ++c){
      vec*cycle = &cycles.ptr[ptr+c];
      int power = k/(needed/size)%size;
      int rewound_cycle[cycle->sz];
      for(int z=0;z<cycle->sz; z++)
        rewound_cycle[z] = cycle->ptr[z];
      for(int j=0,cnt=0; cnt<size; ++cnt,j+=power)
        rewound_cycle[j%size] = cycle->ptr[cnt];
      for(int j=0; j<size; ++j)
        original_cycle[j*needed/size+c]=rewound_cycle[j];
    }
    for(int j=0; j<needed; ++j)
      final[original_cycle[j]]=original_cycle[(j+1)%needed];
    ptr+=needed/size;
    free(original_cycle);
  }
  for(int i=0; i<n; ++i){
    if(i)
      printf(" ");
    printf("%d", final[i]+1);
  }
  puts("");
  free(final);
  return 0;
}
