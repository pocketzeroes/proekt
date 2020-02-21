#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Site{
  int         posX;
  int         posY;
  struct Site*groupID;
  struct Site*oppGroup;
}Site;
Site*sites;


typedef struct{
  int  first;
  Site*second;
  Site*third;
}trip;
trip newtrip(int a, Site*b, Site*c){
  return(trip){a,b,c};
}
#define pbt(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
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
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third )return(a->third  < b->third )?-1:1;
  return 0;
}







//////////////////////////////

int distance(Site*s1, Site*s2){
  return abs(s1->posX - s2->posX) + abs(s1->posY - s2->posY);
}
Site*find(Site*s){
  if(s == NULL) 
    return NULL;
  if(s->groupID == s) 
    return s;
  Site*res = find(s->groupID);
  s->groupID = res;
  return res;
}
void doUnion(Site*s1, Site*s2){
  find(s1)->groupID = find(s2);
}
bool setOpposite(Site*sFrom, Site*sTo){
  if(sFrom->oppGroup == NULL)
    sFrom->oppGroup = sTo;
  else{
    Site*oppElem = find(sFrom->oppGroup);
    doUnion(oppElem, sTo);
    return find(sTo) != find(sTo->oppGroup);
  }
  return true;
}
int main(){
  int nSites;
  scanf("%d", &nSites);
  sites = calloc(nSites, sizeof(Site));
  for(int i=0; i<nSites; i++){
    scanf("%d", &sites[i].posX);
    scanf("%d", &sites[i].posY);
    sites[i].groupID = &sites[i];
    sites[i].oppGroup = NULL;
  }
  vect edges = newVecT();//of trip{int, Site*, Site*}
  for(int i=0; i<nSites; i++){
    for(int j=i+1; j<nSites; j++){
      int dist = distance(&sites[i], &sites[j]);
      pbt(edges, newtrip(-dist, &sites[i], &sites[j]));
    }
  }
  qsort(edges.ptr, edges.sz, sizeof(trip), cmpT);
  int biggestDist = 0;
  for(int z=0;z<edges.sz;z++){trip e = edges.ptr[z];
    Site*s1 = e.second;
    Site*s2 = e.third;
    bool couldSetOpposite = setOpposite(s1, s2) && setOpposite(s2, s1);
    if(!couldSetOpposite){
      biggestDist = -e.first;
      break;
    }
  }
  printf("%d\n", biggestDist);
  return 0;
}
