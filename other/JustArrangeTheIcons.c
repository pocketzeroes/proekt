#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

///////////////////

void solve(){
  int n;
  scanf("%d", &n);
  int A[n]; clr(A);
  for(int i=0; i<n; i++){
    int x;
    scanf("%d", &x);
    x--;
    A[x]++;
  }
  int lol =(int)1e9;
  vec v=newVec();
  for(int i=0; i<n; i++){
    if(A[i]>0){
      pb(v, A[i]);
      lol = fmin(lol, A[i]);
    }
  }
  pair worked(int s, int num){
    int c = num / s;
    int rem = num % s;
    if (rem == 0)
      return newpair(true, c);
    if (s - 1 - rem <= c)
      return newpair(true, c + 1);
    return newpair(false, 0);
  }
  int res =(int)1e9;
  for(int s=2; s<=lol+1; s++){
    int tot = 0;
    bool good = true;
    for(int z=0;z<v.sz;z++){int num = v.ptr[z];
      pair rv = worked(s, num);
      bool bul=rv.first;
      int  cnt=rv.second;
      good &= bul;
      tot += cnt;
    }
    if(good)
      res = fmin(res, tot);
  }
  printf("%d\n", res);
}
int main(){
  int t;
  scanf("%d", &t);
  while(t--)
    solve();
  return 0;
}
