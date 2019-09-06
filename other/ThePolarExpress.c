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

int N;
int O[200];
vec ans;


bool Read(int*first){
  char c,r=0,n=0;
 *first=0;
  for(;;){
   c=getchar();
    if ((c<0) && (!r))
     return(0);
    if ((c=='-') && (!r))
     n=1;
    else
    if ((c>='0') && (c<='9'))
    *first = *first * 10+c-'0',r=1;
    else if (r)
     break;
  }
  if (n)
    *first = - *first;
  return 1;
}
void Go(int first){
  int i, j;
  int tmp[200];
  j = 0;
  for (i = first; i <= N - 1; i++)
    tmp[j++] = O[i];
  for (i = (first)-1; i >= 0; i--)
    tmp[j++] = O[i];
  memcpy(O, tmp, sizeof(O));
  pb(ans, first);
}
int Fnd(int v) {
  int i;
  for (i = 0; i < N; i++) if (O[i] == v) break;
  return (i);
}
int main(){
  int i, e;
  Read(&N);
  for (i = 0; i < N; i++) 
    Read(&O[i]);
  for (;;) {
    i = Fnd(1), e = 1;
    while ((i + 1 < N) && (O[i + 1] == e + 1))
      i++, e++;
    if (e == N) 
      break;
    Go(N);
    if (Fnd(e)) 
      Go(Fnd(e));
    Go(Fnd(1) + 1);
    Go(Fnd(e + 1) + 1);
  }
  printf("%d\n", ans.sz);
  for (i = 0; i < ans.sz; i++)
    printf("%d\n", ans.ptr[i]);
  return 0;
}
