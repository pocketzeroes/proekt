#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

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
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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

//////////////////////////////
int main(){
    double cap;
    int    items;
    while(scanf("%lf %d", &cap, &items)==2){
        int capacity = floor(cap);
        int v[items+1][capacity+1]; clr(v);
        vecp objects = newVecP();
        pbp(objects, newpair(0,0));
        for(int i=0; i<items; i++){
            pair p;
            scanf("%d %d", &p.first, &p.second);
            pbp(objects, p);
        }
        for(int i=1; i<objects.sz; i++){
            pair object = objects.ptr[i];
            for(int j=1; j<=capacity; j++){
                if(j < object.second){
                    v[i][j] = v[i-1][j];
                    continue;
                }
                v[i][j] = fmax(v[i-1][j-object.second]+object.first, v[i-1][j]);
            }
        }
        vec result = newVec();
void restore(int i, int j){
    if(v[i][j] == 0)
        return;
    if(v[i-1][j] == v[i][j])
        restore(i-1, j);
    else{
        restore(i-1, j-objects.ptr[i].second);
        pb(result, i-1);
    }
}
        restore(items, capacity);
        printf("%d\n", result.sz);
        for(int z=0; z<result.sz; z++)
            printf("%d ", result.ptr[z]);
        puts("");
    }
    return 0;
}
