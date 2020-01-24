#pragma GCC optimize "-O3" // https://codeforces.com/contest/1267/my
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdarg.h>

#define strdup _strdup
int vasprintf(char **str, const char *fmt, va_list args){
  int size = 0;
  va_list tmpa;
  va_copy(tmpa, args);
  size = vsnprintf(NULL, size, fmt, tmpa);
  va_end(tmpa);
  if (size < 0) { return -1; }
  *str = (char *)malloc(size + 1);
  if (NULL == *str) { return -1; }
  size = vsprintf(*str, fmt, args);
  return size;
}
int asprintf(char **str, const char *fmt, ...){
  int size = 0;
  va_list args;
  va_start(args, fmt);
  size = vasprintf(str, fmt, args);
  va_end(args);
  return size;
}

void reverse(char * str){
  if(str){
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do{\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end){
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

/////////////////////

int main(){
    char*str=getstr();
    char prv = '$';
    int cnt = 0;
    char*smth = strdup(str);
    int ssz=0;
    vec Count = newVec();
    for(int z=0; str[z]; z++){char c = str[z];
        if(c == prv)
            cnt++;
        else{
            if(prv != '$'){
                smth[ssz++] = prv;
                pb(Count, cnt);
            }
            prv = c;
            cnt = 1;
        }
    }
    if(prv != '$'){
        smth[ssz++] = prv;
        pb(Count, cnt);
    }
    smth[ssz]='\0';
    if(ssz&1){
        char*rev = strdup(smth);
        reverse(rev);
        if(strcmp(smth, rev)==0){
            for(int i=0; i<ssz/2; i++){
                if(Count.ptr[i]+Count.ptr[ssz-1-i]<3){
                    puts("0");
                    return 0;
                }
            }
            if(Count.ptr[ssz/2]>=2)
                printf("%d\n", Count.ptr[ssz/2]+1);
            else
                puts("0");
        }
        else
            puts("0");
    }
    else
        puts("0");
    return 0;
}
