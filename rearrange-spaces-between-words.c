#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>

char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c", a, b);
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}

#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
char buff[100000];
vecs split(char*s){
  vecs rez=newVecS();
  while(isspace(s[0]))s++;
  while(1){
    sscanf(s, "%s", &buff);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(buff));
    s = strchr(s, ' ');
    if(s==NULL)break;
    while(isspace(s[0]))s++;
    if(s[0]=='\0')break;
  }
  return rez;
}
///////////////////
char*reorderSpaces(char*text){
  int sp = 0;
  for(int z=0;text[z];z++){char c = text[z];
    sp += c == ' ';
  }
  vecs words = split(text);
  int n = words.sz;
  int cnt = n>1?sp/(n-1):0;
  char*ret = strdup(words.ptr[0]);
  for(int i=1; i<n; ++i){
    ret = concats(ret, string(cnt, ' '));
    ret = concats(ret, words.ptr[i]);
  }
  if(sp-cnt*(n-1)>0)
    ret = concats(ret, string(sp-cnt*(n-1), ' '));
  return ret;
}
//int main(){
//  char*kvo=strdup("  this   is  a sentence ");
//  puts(reorderSpaces(kvo));
//  return 0;
//}
