// #define _GNU_SOURCE
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<math.h>
// #include<ctype.h>
// #include<limits.h>
// char *strndup (const char *s, size_t n){
//   char *result;
//   size_t len = strlen (s);
//   if (n < len)
//     len = n;
//   result = (char *) malloc (len + 1);
//   if (!result)
//     return 0;
//   result[len] = '\0';
//   return (char *) memcpy (result, s, len);
// }
char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}
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
int*pushback(int *array, int *size, int value){
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
typedef struct{
    char*s1;
    char*s2;
    int  num;
}Tuple;
Tuple newTuple(char*a, char*b, int c){
    Tuple rez;
    rez.s1  = a;
    rez.s2  = b;
    rez.num = c;
    return rez;
}
Tuple*pushbackT(Tuple*array, int *size, Tuple value){
    Tuple*output = resizeArray(array, Tuple, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    Tuple*ptr;
    int sz;
}vect;
vect newVecT() {
    vect rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

int cmpTuple(const void*pa, const void*pb){
  Tuple*a = (Tuple*)pa;
  Tuple*b = (Tuple*)pb;
  int rv=0;
  rv = strcmp(a->s1 , b->s1); if(rv!=0)return rv;
  rv = strcmp(a->s2 , b->s2); if(rv!=0)return rv;
  if(a->num != b->num)return(a->num < b->num)?-1:1;
  return 0;
}
/////////////////////////

char**reorderLogFiles(char**logs, int logsSz, int*rsz){
    vect A = newVecT();
    vec  D = newVec();
    for(int i=0, i_len=logsSz; i<i_len; ++i){
        char*s = logs[i];
        int k = strchr(s, ' ')-s;
        int a = 0;
        for(int j=k; j<strlen(s); j++){
            if(isalpha(s[j]))
                a++;
        }
        if(a)
            A.ptr = pushbackT(A.ptr, &A.sz, newTuple(s+k, substr(s, 0, k), i));
        else
            D.ptr = pushback(D.ptr, &D.sz, i);
    }
    qsort(A.ptr, A.sz, sizeof(Tuple), cmpTuple);
    vecs ans = newVecS();
    for(int i=0; i<A.sz; i++){ Tuple e = A.ptr[i];
        int i = e.num;
        ans.ptr = pushbackS(ans.ptr, &ans.sz, logs[i]);
    }
    for(int i=0; i<D.sz; i++){int e = D.ptr[i];
        ans.ptr = pushbackS(ans.ptr, &ans.sz, logs[e]);
    }
   *rsz =  ans.sz;
    return ans.ptr;
}

#if 0
int main(){
    return 0;
}
#endif
