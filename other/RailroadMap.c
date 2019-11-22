#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  pair first;
  int  second;
}trip;
trip newtrip(pair a, int b){
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
  int rv = cmpP(&a->first, &b->first);
  if(rv!=0)return rv;
  if(a->second != b->second)return(a->second < b->second )?-1:1;
  return 0;
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

/////////////////////
int kase, N, M;
vecp adjacency[40010];
bool visited  [40010];
vect ret;//of trip{pair,int}

pair recurseIt(int curr, int prevy){
    if(adjacency[curr].sz != 2)
        return newpair(curr, 0);
    visited[curr] = true;
    for(int z=0;z<adjacency[curr].sz;z++){pair e = adjacency[curr].ptr[z];
        if(e.first == prevy)
            continue;
        pair ret = recurseIt(e.first, curr);
        ret.second += e.second;
        return ret;
    }
    return newpair(0, 0);
}
int main(){
    scanf("%d", &kase);
    for(int kk=1; kk<=kase; kk++){
        scanf("%d %d", &N, &M);
        ret.sz=0;
        for(int i=0; i<40010; i++){
            adjacency[i].sz=0;
            visited[i] = false;
        }
        for(int i=0; i<M; i++){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            N++;
            pbp(adjacency[a], newpair(N, c));
            pbp(adjacency[b], newpair(N, c));
            pbp(adjacency[N], newpair(a, c));
            pbp(adjacency[N], newpair(b, c));
        }
        for(int i=1; i<=N; i++){
            if(!visited[i] && adjacency[i].sz == 2){
                visited[i] = true;
                pair a = recurseIt(adjacency[i].ptr[0].first, i), b = recurseIt(adjacency[i].ptr[1].first, i);
                pb(ret, newtrip(newpair(fmin(a.first, b.first), fmax(a.first, b.first)), a.second+b.second+adjacency[i].ptr[0].second+adjacency[i].ptr[1].second));
            }
        }
        printf("%d\n", ret.sz);
        qsort(ret.ptr, ret.sz, sizeof(trip), cmpT);
        for(int i=0; i<ret.sz; i++)
            printf("%d %d %d\n", ret.ptr[i].first.first, ret.ptr[i].first.second, ret.ptr[i].second/2);
        puts("");
    }
    return 0;
}
