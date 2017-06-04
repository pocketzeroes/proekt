#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include <ctype.h>

typedef char* string;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
string *pushback(string *array, int *size, string value) {
    string *output = resizeArray(array, string, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	string*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define MAX_NB_ARR 100000
int hashes[MAX_NB_ARR];
vec vecstr[MAX_NB_ARR];
int hashesSz;
void put(int h, char*str){
    bool found=false;
    int i;
    for(i=0;i<hashesSz;i++){
        if(hashes[i]==h){
            found=true;
            break;
        }
    }
    vecstr[i].ptr = pushback(vecstr[i].ptr, &vecstr[i].sz, str);
    if(!found){
        hashes[i]=h;
        hashesSz++;
    }
}
char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s",a,b);
  return ptr;
}
int dohash(char*a){
#define PRIME_NUMBER 256203161
    unsigned hash = PRIME_NUMBER;
    for (int j = 0; a[j]; j++)
      hash = hash * PRIME_NUMBER + a[j];
    return hash;
}
void solve(char* str) {
    char* root = strdup("");
    int index = 0;
    while (str[index] != ' ') {
        root = concat(root, str[index++]);
    }
    root = concat(root, '/');
    ++index;
    char* name   =strdup(""); 
    char* content=strdup("");
    int flag = 0;
    for (; str[index]; ++index) {
        if (str[index] == ' ') {
            continue;
        }
        if (str[index] == '(') {
            flag = 1;
        }
        else if (str[index] == ')') {
            int hh = dohash(content);
            char*root_name = concats(root , name);
            put(hh, root_name);
//            printf("map[%s] hh=%d pushback %s\n", content, hh, root_name);
            flag = 0;
if(name)   free(name);    name    = strdup(""); 
if(content)free(content); content = strdup("");
        }
        else {
            if (flag == 0) {
                name = concat(name, str[index]);
            }
            else {
                content=concat(content, str[index]);
            }
        }
    }
}
char*** findDuplicate(char** paths, int pathsSize, int**colSzs, int* retSz) {
    hashesSz=0;
    memset(hashes,0,sizeof(hashes));
    memset(vecstr,0,sizeof(vecstr));

    for(int i=0;i<pathsSize;i++)
        solve(paths[i]);
    char***res = calloc(hashesSz, sizeof(char**));
    int*cols   = calloc(hashesSz, sizeof(int));
    int c=0;
    for(int i=0;i<hashesSz;i++){
        if(vecstr[i].sz>1){
            cols[c]=vecstr[i].sz;
            res [c]=vecstr[i].ptr;
            c++;
        }
    }
   *colSzs=cols;
   *retSz=c;
    return res;
}

#ifdef _WIN32
int main(){
    char*arr[4]={"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"};
    int*csz;
    int rsz;
    findDuplicate(arr, 4, &csz, &rsz);
    printf("rsz=%d\n", rsz);
}
#endif

















































