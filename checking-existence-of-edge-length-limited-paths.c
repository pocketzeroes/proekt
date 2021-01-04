#pragma GCC optimize "-O3" // https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define fi first
#define se second

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}

typedef struct{
  pair first, second;
}quad;
quad newquad(pair a, pair b){
  return(quad){a,b};
}

int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

int cmpQ(const void*pa, const void*pb){
  quad*a = (quad*)pa;
  quad*b = (quad*)pb;
  int rv=0;
  rv=cmpP(&a->fi, &b->fi); if(rv!=0) return rv;
  rv=cmpP(&a->se, &b->se); if(rv!=0) return rv;
  return 0;
}

typedef struct{
  int   first;
  pair second;
}trip;
trip newtrip(int a, pair b){
  return(trip){a,b};
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)
    return(a->first < b->first )?-1:1;
  return cmpP(&a->second, &b->second);
}
/////////////////////////////
int f[100005];
int Find(int x){
    if(f[x]==x)
      return x;
    return f[x]=Find(f[x]);
}
bool*distanceLimitedPathsExist(int n, int**edgeList, int edgeListSz, int*edgeList0sz, int**queries, int queriesSz, int*queries0sz, int*rsz){
    quad*v = calloc(queriesSz, sizeof(quad));//of quad{pair,pair}
    int index=0;
    int vsz=queriesSz;
    for(int i=0;i<queriesSz;i++){int*it=queries[i];
        v[i]=newquad(newpair(it[2],index++),newpair(it[0],it[1]));
    }
    qsort(v, vsz, sizeof(quad), cmpQ);
    for(int i = 0;i<n;i++)
      f[i]=i;    
    trip*edge=calloc(edgeListSz, sizeof(trip));//of trip{int,pair}
    bool*ans=calloc(queriesSz, sizeof(bool));
    for(int i=0;i<edgeListSz;i++){int*it=edgeList[i];
        edge[i]=newtrip(it[2],newpair(it[0],it[1]));
    }
    qsort(edge, edgeListSz, sizeof(trip), cmpT);
    int now=0;
    for(int i=0;i<edgeListSz;i++){trip it=edge[i];
        while(now!=vsz&&v[now].fi.fi<=it.fi){
            ans[v[now].fi.se]=(Find(v[now].se.fi)==Find(v[now].se.se));
            now++;
        }
        int a=Find(it.se.fi),
            b=Find(it.se.se);
        f[a]=b;
    }
    while(now!=vsz){
        ans[v[now].fi.se]=(Find(v[now].se.fi)==Find(v[now].se.se));
        now++;
    }
   *rsz=queriesSz;
    return ans;
}
