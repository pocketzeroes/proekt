#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct pair{
  int  first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushback(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int n, m;
vecp V;
int main(){
    scanf("%d %d", &n, &m);
    if (n == 1)
        return puts("0")*0;
    if((n == 3 && m == 0) || (n == 2 && m == 0)) 
        return puts("-1")*0;
    for (int i = 1; i < n; i++) 
        V.ptr = pushback(V.ptr, &V.sz, newPair(i, i+1));
    if (!m){
        for (int i = 3; i <= n; i++) 
            V.ptr = pushback(V.ptr, &V.sz, newPair(1, i));
        V.ptr = pushback(V.ptr, &V.sz, newPair(2, n));
    }
    else{
        int cnt = n - 1 - m;
        for (int i = 1; i <= cnt; i++) 
            V.ptr = pushback(V.ptr, &V.sz, newPair(1, 2 + i));
    }
    printf("%d\n", V.sz);
    int k = 0;
    for(int z=0;z<V.sz;z++){pair it = V.ptr[z];
        printf("%d %d %d\n", it.first, it.second, ++k);
    }
}



