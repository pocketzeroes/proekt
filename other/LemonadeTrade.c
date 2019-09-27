#pragma GCC optimize "-O3"
#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
const ld inf = 1e9;
#define pb(zpv, zvv) zpv.ptr = pushbackPpl(zpv.ptr, &zpv.sz, zvv)
#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
int unique(char**a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(strcmp(a[i], a[j])!=0)
      a[++j] = a[i];
  return j + 1;
}

typedef struct{
  char*first;
  char*second;
}pss;
pss newpss(char*a, char*b){
  return(pss){a,b};
}

typedef struct{
  pss first;
  ld  second;
}trip;
trip newtrip(pss a, ld b){
  return(trip){a,b};
}
trip*pushbackT(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    trip*ptr;
    int sz;
}vect;
vect newVecT() {
    vect rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  pair first;
  ld   second;
}ppl;
ppl newppl(pair a, ld b){
  return(ppl){a,b};
}
ppl*pushbackPpl(ppl*array, int *size, ppl value){
  ppl*output = resizeArray(array, ppl, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ppl*ptr;
	int sz;
}vecppl;
vecppl newVecPpl(){
	vecppl rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

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

// pss  = {str, str}
// trip = {pss, ld}
// ppl  = {pair, ld}

int main(){
    int n;
    scanf("%d", &n);
    vect   offers  = newVecT();//of trip
    vecppl revised = newVecPpl();
    vecs   strings = newVecS();
    pbs(strings, strdup("blue"));
    pbs(strings, strdup("pink"));
    for(int i=0; i<n; ++i){
        char*a = getstr();
        char*b = getstr();
        ld ratio;
        scanf("%Lf", &ratio);
        pbs(strings, a);
        pbs(strings, b);
        offers.ptr = pushbackT(offers.ptr, &offers.sz, newtrip(newpss(a, b), ratio));
    }
    qsort(strings.ptr, strings.sz, sizeof(char*), cmpstr);
    strings.sz = unique(strings.ptr, strings.sz);
    int m = strings.sz;
    for(int i=0; i<offers.sz; ++i){
        int low = 0;
        int high = m - 1;
        while(low != high){
            int mid = (low + high) / 2;
            if(strcmp(strings.ptr[mid], offers.ptr[i].first.first)<0)
                low = mid + 1;
            else
                high = mid;
        }
        int first = low;
        low = 0;
        high = m - 1;
        while(low != high){
            int mid = (low + high) / 2;
            if(strcmp(strings.ptr[mid], offers.ptr[i].first.second)<0)
                low = mid + 1;
            else
                high = mid;
        }
        int second = low;
        pb(revised, newppl(newpair(first, second), offers.ptr[i].second));
    }
    int pink = -1;
    int blue = -1;
    for(int i=0; i<m; ++i){
        if(strcmp(strings.ptr[i], "pink")==0)
            pink = i;
        else if(strcmp(strings.ptr[i], "blue")==0)
            blue = i;
    }
    ld amounts[m];
    for(int i=0; i<m; ++i)
        amounts[i] = -inf;
    amounts[pink] = 0.;
    for(int i=0; i<revised.sz; ++i){
        int o = revised.ptr[i].first.first;
        int w = revised.ptr[i].first.second;
        amounts[o] = fmaxl(amounts[o], amounts[w] + logl(revised.ptr[i].second));
    }
    if(amounts[blue] > logl(10.))
        puts("10");
    else
        printf("%.20Lf\n", expl(amounts[blue]));
    return 0;
}
