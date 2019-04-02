#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
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

enum{BUCKET_SZ=1000001};
vec size_bucket[BUCKET_SZ];

int main(){
  int n;
  scanf("%d", &n);
  int size[n]; memset(size,0,sizeof(size));
  int deps[n]; memset(deps,0,sizeof(deps));
  vec edge[n]; memset(edge,0,sizeof(edge));
  for (int i=0,d; i<n; i++){
    scanf("%d %d", &size[i], &d);
    for(int j=0; j<d; j++){
        int x;
        scanf("%d", &x);
        --x;
        edge[i].ptr = pushback(edge[i].ptr, &edge[i].sz, x);
        ++deps[x];
    }
    size_bucket[size[i]].ptr = pushback(size_bucket[size[i]].ptr, &size_bucket[size[i]].sz, i);
    ++deps[i];
  }
  vec by_size = newVec();
  for(int z=0;z<BUCKET_SZ;z++){
    for(int q=0;q<size_bucket[z].sz;q++){
      by_size.ptr = pushback(by_size.ptr, &by_size.sz, size_bucket[z].ptr[q]);
    }
  }
  int limit=0;
  vec todo = newVec();
  for(int i=0,j=0; i<n; i++){
    for(;j<n && (i==todo.sz || size[by_size.ptr[j]]+(n-1-i)<=limit); ++j){
      if (! --deps[by_size.ptr[j]]){
        limit = max(limit, size[by_size.ptr[j]]+(n-1-i));
        todo.ptr = pushback(todo.ptr, &todo.sz, by_size.ptr[j]);
      }
    }
    for(int z=0;z<edge[todo.ptr[i]].sz;z++){int y = edge[todo.ptr[i]].ptr[z];
      if(!--deps[y]){
        todo.ptr = pushback(todo.ptr, &todo.sz, y);
      }
    }
  }
  printf("%d\n", limit);
  return 0;
}
