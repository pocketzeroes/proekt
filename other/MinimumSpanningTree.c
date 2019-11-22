#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  int   first;
  pair second;
}trip;
trip newtrip(int a, pair b){
  return(trip){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)return(a->first < b->first )?-1:1;
  return cmpP(&a->second, &b->second);
}

#define pb(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
  trip*output = resizeArray(array, trip, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  trip*ptr;
  int sz;
}vect;
vect newVecT(){
  vect rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
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

/////////////////////////////////
int N, M, parents [20010], heights [20010], totalWeight;
trip edges [30010];//trip {int, pair}
vecp mst;

int findParent(int x){
    if(x == parents[x])
        return x;
    parents[x] = findParent(parents[x]);
    return parents[x];
}
bool combine(int x, int y){
    int a = findParent(x);
    int b = findParent(y);
    if(a == b) 
        return false;
    if(heights[b] < heights[a]) 
        parents[b] = a;
    else if(heights[a] < heights[b]) 
        parents[a] = b;
    else{
        parents[b] = a;
        heights[a]++;
    }
    return true;
}
int main(){
    while(1){
        scanf("%d %d", &N, &M);
        if(N == 0 && M == 0) 
            break;
        for(int i=0; i<N; i++){
            parents[i] = i;
            heights[i] = 0;
        }
        for(int i=0; i<M; i++){
            scanf("%d %d %d", &edges[i].second.first, &edges[i].second.second, &edges[i].first);
            if(edges[i].second.first > edges[i].second.second)
                swap(edges[i].second.first, edges[i].second.second);
        }
        qsort(edges, M, sizeof(trip), cmpT);
        totalWeight = 0;
        mst.sz=0;
        for(int i=0; i<M; i++){
            bool ok = combine(edges[i].second.first, edges[i].second.second);
            if(!ok) 
                continue;
            totalWeight += edges[i].first;
            pbp(mst, edges[i].second);
            if(mst.sz == N-1)
                break;
        }
        if(mst.sz == N-1){
            printf("%d\n", totalWeight);
            qsort(mst.ptr, mst.sz, sizeof(pair), cmpP);
            for(int i=0; i<N-1; i++)
                printf("%d %d\n", mst.ptr[i].first, mst.ptr[i].second);
        }
        else
            puts("Impossible");
    }
    return 0;
}
