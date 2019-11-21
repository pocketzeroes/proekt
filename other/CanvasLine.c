#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
///////////////////////////////
enum{ N = 1010};
int a[N], b[N];
vec pegs;

bool have_peg(int x){
  for(int z=0; z<pegs.sz; z++)
    if(pegs.ptr[z]==x)
      return true;
  return false;
}
int count_pegs(int i){
  int cnt=0;
  for(int z=0; z<pegs.sz; z++){int x = pegs.ptr[z];
    if(a[i]<=x && x<=b[i])
      cnt++;
  }
  return cnt;
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    scanf("%d %d", &a[i], &b[i]);
  int p;
  scanf("%d", &p);
  pegs.ptr = calloc(p, sizeof(int));
  pegs.sz = p;
  for(int z=0; z<pegs.sz; z++){
    scanf("%d", &pegs.ptr[z]);
  }
  for(int i=0; i<n; i++){
    if(count_pegs(i)>2){
      puts("impossible");
      return 0;
    }
  }
  for(int i=1; i<n; i++){
    if(b[i-1]<a[i]||have_peg(a[i]))
      continue;
    if(fmax(count_pegs(i-1), count_pegs(i))<2)
      pb(pegs, a[i]);
  }
  for(int i=0; i<n; i++){
    for(int x=a[i]+1; count_pegs(i)<2; x++){
      if(have_peg(x))
        continue;
      pb(pegs, x);
    }
  }
//erase(&pegs, 0, p);
  int*pptr=pegs.ptr+p;
  int psz =pegs.sz-p;
  printf("%d\n", psz);
  for(int z=0; z<psz; z++){
    printf("%d ", pptr[z]);
  }
  puts("");
  return 0;
}
