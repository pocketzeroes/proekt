#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  if(rv!=1) return NULL;
  return strdup(buff);
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

int main(){
    vec bits = newVec();
    char*s;
    while((s=getstr())!=NULL){
        bool isGood = true;
        for(int z=0;s[z];z++){char c=s[z];
            if(isalnum(c) && c != 'u' && c != 'm')
                isGood = false;
        }
        if(isGood)
            for(int z=0;s[z];z++){char c=s[z];
                if(isalnum(c))
                   pb(bits, (c=='u'));
            }
    }
    for(int i=0; i<bits.sz; i+=7){
        char val=0;
        for(int j=0; j<7; j++)
            val = val*2+bits.ptr[i+j];
        putchar(val);
    }
    puts("");
    return 0;
}
