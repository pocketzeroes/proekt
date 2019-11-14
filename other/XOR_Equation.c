#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef unsigned long long ll;

char*to_string(ll v){
  char*ptr=NULL;
  asprintf(&ptr, "%llu", v);
  return ptr;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


ll sz;
ll temp;

typedef char* str;

ll count(char*s){
    ll ct = 0;
    for(int z=0;s[z];z++){char i = s[z];
        if(i == '?')
            ct++;
    }
    return ct;
}
int cmp(const void*pa, const void*pb){
    str*s1=(str*)pa;
    str*s2=(str*)pb;
    return(count(*s1) < count(*s2))?-1:1;
}
bool works(ll t, char*s){
    char*o = to_string(t);
    if(strlen(o) != sz)
        return false;
    if((strcmp(s, "?")==0 || strcmp(s, "0")==0) && strcmp(o, "0")==0)
        return true;
    if(s[0] == '0')
        return false;
    for(ll i=0; s[i]; i++){
        if(s[i] != o[i] && s[i] != '?')
            return false;
    }
    return true;
}
void permute(vecl*v, char*s, ll pos){
    int ssize = strlen(s);
    if(pos == ssize){
        v->ptr = pushbackL(v->ptr, &v->sz, temp);
        return;
    }
    if(s[pos] == '?'){
        temp *= 10;
        ll i = 0;
        if(pos == 0 && ssize > 1)
            i = 1;
        for(; i < 10; i++){
            temp += i;
            permute(v, s, pos+1);
            temp -= i;
        }
        temp /= 10;
    }
    else{
        temp *= 10;
        temp += s[pos] - '0';
        permute(v, s, pos+1);
        temp -= s[pos] - '0';
        temp /= 10;
    }
}
int main(){
    char*v[3];
    v[0]=getstr();
    getstr();
    v[1]=getstr();
    getstr();
    v[2]=getstr();
    qsort(v, 3, sizeof(char*), cmp);
    vecl v1 = newVecL();
    vecl v2 = newVecL();
    permute(&v1, v[0], 0);
    permute(&v2, v[1], 0);
    sz = strlen(v[2]);
    ll ways = 0;
    for(int z=0; z<v1.sz; z++){ll i = v1.ptr[z];
        for(int q=0; q<v2.sz; q++){ll j = v2.ptr[q];
            if(works(i^j, v[2]))
                ways++;
        }
    }
    for(ll i=0; i<=2; i++)
        if(strcmp(v[i], "0")!=0 && v[i][0] == '0')
            ways = 0;
    printf("%lld\n", ways);
    return 0;
}
