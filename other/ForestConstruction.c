#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define back(vv) vv.ptr[vv.sz-1]
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
//////////////

int main(){
    int v;
    scanf("%d", &v);
    vecp inter=newVecP();
    vec leaves=newVec();
    vecp edges=newVecP();
    for(size_t i = 0; i < v; ++i){
        int t;
        scanf("%d", &t);
        if(t == 1)
            pb(leaves, i);
        else if (t >= 2)
            pbp(inter, newpair(i, t));
    }
    for(size_t i=0; i<inter.sz; ++i){
        if(i < inter.sz - 1){
            pbp(edges, newpair(inter.ptr[i].first, inter.ptr[i+1].first));
            inter.ptr[i  ].second--;
            inter.ptr[i+1].second--;
        }
        while(inter.ptr[i].second > 0){
            if(leaves.sz==0)
                return puts("IMPOSSIBLE")*0;
            pbp(edges, newpair(inter.ptr[i].first, back(leaves)));
            leaves.sz--;
            inter.ptr[i].second--;
        }
    }
    if(leaves.sz % 2 != 0)
        return puts("IMPOSSIBLE")*0;
    for(size_t i=0; i<leaves.sz; i+=2)
        pbp(edges, newpair(leaves.ptr[i], leaves.ptr[i+1]));
    qsort(edges.ptr, edges.sz, sizeof(pair), cmpP);
    puts("POSSIBLE");
    for(int z=0;z<edges.sz;z++){pair edge = edges.ptr[z];
        printf("%d %d\n", edge.first+1, edge.second+1);
    }
    return 0;
}
