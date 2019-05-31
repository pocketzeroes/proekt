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



enum{ N = 110};
vec kraw[N];
int t[N][N];
int used[N];
int n;

int go(int i, int k){
  if (k <= 0)
    return 1;
  if (i >= n)
    return 0;
  if (used[i])
    return go(i+1,k);
  vec v = newVec();
  used[i] = 1;
  for(int z=0;z<kraw[i].sz;z++){int it=kraw[i].ptr[z];
    if(!used[it]){
      v.ptr = pushback(v.ptr, &v.sz, it);
      used[it] = 1;
    }
  }
  if(go(i+1,k-1))
    return 1;
  for(int z=0;z<v.sz;z++){int it=v.ptr[z];
    used[it] = 0;
  }
  vec v2 = newVec();
  for(int a=0; a<v.sz; ++a){
    for(int b=0; b<(a); ++b){
      if(!t[v.ptr[a]][v.ptr[b]]){
        used[v.ptr[a]] = 1;
        used[v.ptr[b]] = 1;
        for(int z=0; z<kraw[v.ptr[a]].sz; z++){int it=kraw[v.ptr[a]].ptr[z];
          if(!used[it])
            v2.ptr = pushback(v2.ptr, &v2.sz, it);
        }
        for(int z=0;z<kraw[v.ptr[b]].sz;z++){int it=kraw[v.ptr[b]].ptr[z];
          if(!used[it])
            v2.ptr = pushback(v2.ptr, &v2.sz, it);
        }
        for(int z=0;z<v2.sz;z++){int it=v2.ptr[z];
          used[it] = 1;
        }
        if(go(i+1,k-2))
          return 1;
        for(int z=0;z<v2.sz;z++){int it=v2.ptr[z];
          used[it] = 0;
        }
        v2.sz=0;
        used[v.ptr[a]] = 0;
        used[v.ptr[b]] = 0;
      }
    }
  }
  used[i] = 0;
  return 0;
}
int main(){
  int k;
  scanf("%d %d", &k, &n);
  if(n >= 5 * k){
    puts("possible");
    return 0;
  }
  for(int i=0; i<n; i++){
    int x;
    scanf("%d", &x);
    while(x--){
      int y;
      scanf("%d", &y);
      kraw[i].ptr = pushback(kraw[i].ptr, &kraw[i].sz, --y);
      t[i][y] = 1;
    }
  }
  puts(go(0,k) ? "possible" : "impossible");
  return 0;
}
