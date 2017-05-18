#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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

////
bool doit(int*a,int asz,  int*b,int bsz){
  if(asz != bsz)
    return false;
  if(asz <= 1)
    return true;
  vec al = newVec();
  vec ar = newVec();
  vec bl = newVec();
  vec br = newVec();
  for(int i = 1; i < asz; i++){
    if(a[i]<a[0]) al.ptr = pushback(al.ptr, &al.sz, a[i]); else ar.ptr= pushback(ar.ptr, &ar.sz, a[i]);
    if(b[i]<b[0]) bl.ptr = pushback(bl.ptr, &bl.sz, b[i]); else br.ptr= pushback(br.ptr, &br.sz, b[i]);
  }
  return doit(al.ptr,al.sz, bl.ptr,bl.sz)&& 
         doit(ar.ptr,ar.sz, br.ptr,br.sz);
}
int main() {
  int N, K;
  scanf("%d %d", &N, &K);
  do{
    int tree[N][K];
    int ret = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < K; j++) 
        scanf("%d", &tree[i][j]);
      int j;
      for (j = 0; j < i; j++)
        if(doit(tree[i],K, tree[j],K))
          break;
      if (j == i) 
        ret++;
    }
    printf("%d\n", ret);
  }while(0);
}


























