#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////
char buff[100000];
vec pos[26];
int main(){
    scanf("%s", &buff);
    int n = strlen(buff);
    for(int i = 0; i < n; i++){
        int idx=buff[i] - 'a';
        pos[idx].ptr = pushback(pos[idx].ptr, &pos[idx].sz, i);
    }
    int mx_num = 0;
    for(int i = 0; i < 26; i++)
        mx_num = max(mx_num, pos[i].sz);
    char*mx_answer = strdup("");
    for(int i = 0; i < 26; i++){
        int size = 1;
        if(pos[i].sz != mx_num)
            continue;
        while(pos[i].ptr[pos[i].sz-1] + size < n){
            char ch = buff[pos[i].ptr[0] + size];
            bool ok = true;
            for(int z=0;z<pos[i].sz;z++){int itr = pos[i].ptr[z];
                if(buff[itr + size] != ch)
                    ok = false;
            }
            if (!ok) 
                break;
            size++;
        }
        char*c_str = strdup("");
        for(int j = 0; j < size; j++) 
            c_str = concat(c_str, buff[pos[i].ptr[0] + j]);
        if(size > strlen(mx_answer) || strcmp(mx_answer, c_str) > 0){
            if(mx_answer){ free(mx_answer); mx_answer = NULL;}
            mx_answer = strdup(c_str);
        }
    }
    puts(mx_answer);
    return 0;
}













