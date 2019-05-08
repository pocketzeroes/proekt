#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int main(){
  char*aux;
  vecp queens = newVecP();
  for(int i = 0; i < 8; i++){
    aux = getstr();
    for(int j = 0; j < 8; j++){
      if(aux[j] == '*')
        queens.ptr = pushbackP(queens.ptr, &queens.sz, newPair(i,j));
    }
  }
  for(int i = 0; i < queens.sz; i++)
    for(int j = i+1; j < queens.sz; j++)
      if(queens.ptr[i].first  == queens.ptr[j].first ||
         queens.ptr[i].second == queens.ptr[j].second||
         abs(queens.ptr[i].first  - queens.ptr[j].first ) ==
         abs(queens.ptr[i].second - queens.ptr[j].second)  ){
        puts("invalid");
        return 0;
      }
  if(queens.sz==8)
    puts("valid");
  else
    puts("invalid");
  return 0;
}
