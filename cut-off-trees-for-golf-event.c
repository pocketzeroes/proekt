#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct pairS{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair *pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecpS {
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///
typedef struct tripS{
  int first ;
  int second;
  int third ;
}trip;
trip newTrip(int _x, int _y, int _z){
  trip rez;
  rez.first =_x;
  rez.second=_y;
  rez.third =_z;
  return rez;
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
vect newVecT(){
	vect rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  diff = a->second - b->second; if(diff!=0) return diff;
  return a->third  - b->third;
}

////////////////////////////////
int neigh[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int d[51][51][51][51];

int cutOffTree(int**forest, int forestSz, int*forest_size){
  vect a = newVecT();
  int i, j, k, m, n, ans, x, y, z, l;
  vecp q = newVecP();
  m = forestSz;
  n = forest_size[0];
  memset(d, -1, sizeof(d));
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      if(forest[i][j]>=2)
        a.ptr = pushbackT(a.ptr, &a.sz, newTrip(forest[i][j], i, j) );
      if(forest[i][j]==0)
        continue;
      q.sz=0;
      q.ptr = pushbackP(q.ptr, &q.sz, newPair(i,j));
      d[i][j][i][j]=0;
      for(k=0; k<q.sz; k++){
        z = d[i][j][q.ptr[k].first][q.ptr[k].second];
        for(l=0;l<4;l++){
          x=q.ptr[k].first +neigh[l][0];
          y=q.ptr[k].second+neigh[l][1];
          if((x>=0)&&(x<m)&&(y>=0)&&(y<n)&&(forest[x][y]!=0)&&(d[i][j][x][y]==-1)){
            d[i][j][x][y]=z+1;
            q.ptr = pushbackP(q.ptr, &q.sz, newPair(x,y));
          }
        }
      }
    }
  }
  a.ptr = pushbackT(a.ptr, &a.sz, newTrip(0,0,0));
  qsort(a.ptr, a.sz, sizeof(trip), cmpT);
  ans=0;
  for(i=0;i+1<a.sz;i++){
    if(d[a.ptr[i].second][a.ptr[i].third][a.ptr[i+1].second][a.ptr[i+1].third]==-1) 
      return -1;
    ans += d[a.ptr[i].second][a.ptr[i].third][a.ptr[i+1].second][a.ptr[i+1].third];
  }
  return ans;
}




















