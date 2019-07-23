#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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
//////////////////////////////////
int n, m, k, myClock;

vec*  T;
vec*  ID;
vec*  ministersInCity;
bool* onDFSStack;
int*  pre;
int*  post;
int*  val;
vecp* importantCityList;
vec*  importantCitiesOfMinister;
int*  possibleRootOfMinister;
vec   importantTracks;
vec   DFSStack;


void initialize(){
  scanf("%d %d %d", &n, &m, &k);
  onDFSStack        = calloc(n, sizeof(bool));
  pre               = calloc(n, sizeof(int));
  post              = calloc(n, sizeof(int));
  val               = calloc(n, sizeof(int));
  T                 = calloc(n, sizeof(vec));
  ID                = calloc(n, sizeof(vec));
  ministersInCity   = calloc(n, sizeof(vec));
  importantCityList = calloc(n, sizeof(vecp));
  for(int i = 1; i <= n-1; ++i){
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    T [u].ptr=pushback(T [u].ptr, &T [u].sz, v);
    T [v].ptr=pushback(T [v].ptr, &T [v].sz, u);
    ID[u].ptr=pushback(ID[u].ptr, &ID[u].sz, i);
    ID[v].ptr=pushback(ID[v].ptr, &ID[v].sz, i);
  }
  possibleRootOfMinister    = calloc(m, sizeof(int)); fill(possibleRootOfMinister, m, -1);
  importantCitiesOfMinister = calloc(m, sizeof(vec));
  for(int i = 0; i < m; ++i){
    int si;
    scanf("%d", &si);
    for(int j = 0; j < si; ++j) {
      int city;
      scanf("%d", &city);
      city--;
      ministersInCity[city].ptr = pushback(ministersInCity[city].ptr, &ministersInCity[city].sz, i);
    }
  }
}
void prePostDFS(int pos){
  pre[pos] = ++myClock;
  onDFSStack[pos] = true;
  for(int i = 0; i < T[pos].sz; ++i){
    int ch = T[pos].ptr[i];
    if(onDFSStack[ch])
      continue;
    prePostDFS(ch);
  }
  onDFSStack[pos] = false;
  post[pos] = ++myClock;
}
void importantCityDFS(int pos){
  onDFSStack[pos] = true;
  for(int i = 0; i < ministersInCity[pos].sz; ++i){
    int minister = ministersInCity[pos].ptr[i];
    while(importantCitiesOfMinister[minister].sz>0 && post[importantCitiesOfMinister[minister].ptr[importantCitiesOfMinister[minister].sz-1]] > pre[pos]){
      importantCitiesOfMinister[minister].sz--;
    }
    importantCitiesOfMinister[minister].ptr = pushback(importantCitiesOfMinister[minister].ptr, &importantCitiesOfMinister[minister].sz, pos);
  }
  for(int i = 0; i < T[pos].sz; ++i){
    int ch = T[pos].ptr[i];
    if(onDFSStack[ch])
      continue;
    importantCityDFS(ch);
  }
  for(int i = 0; i < ministersInCity[pos].sz; ++i) {
    int minister = ministersInCity[pos].ptr[i];
    possibleRootOfMinister[minister] = pos;
  }
  onDFSStack[pos] = false;
}
void setPositiveValues(){
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < importantCitiesOfMinister[i].sz; ++j){
      val[importantCitiesOfMinister[i].ptr[j]]++;
    }
  }
}
void setImportantCityList(){
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < importantCitiesOfMinister[i].sz; ++j){
      int thisCity = importantCitiesOfMinister[i].ptr[j];
      importantCityList[thisCity].ptr = pushbackP(importantCityList[thisCity].ptr, &importantCityList[thisCity].sz, newPair(i, j));
    }
  }
}
bool isAncestorOf(int possibleParent, int possibleChild){
  return post[possibleParent] > post[possibleChild];
}
int LCA(int pos, int lb, int targetCity) {
  int city = DFSStack.ptr[pos];
  if(lb + 1 >= pos) {
    if(isAncestorOf(city, targetCity))
      return city;
    return DFSStack.ptr[lb];
  }
  int test = (pos + lb) / 2;
  int testCity = DFSStack.ptr[test];
  if(isAncestorOf(testCity, targetCity)){
    return LCA(pos, test, targetCity);
  }
  return LCA(test, lb, targetCity);
}
void setNegativeValueDFS(int pos){
  DFSStack.ptr = pushback(DFSStack.ptr, &DFSStack.sz, pos);
  onDFSStack[pos] = true;
  for(int i = 0; i < importantCityList[pos].sz; ++i){
    int minister = importantCityList[pos].ptr[i].first;
    int j = importantCityList[pos].ptr[i].second;
    if(j + 1 == importantCitiesOfMinister[minister].sz) 
      continue;
    int nextCity = importantCitiesOfMinister[minister].ptr[j+1];
    int stackSize = DFSStack.sz;
    int minusPos = LCA(stackSize - 1, 0, nextCity);
    if(post[minusPos] > post[possibleRootOfMinister[minister]])
      possibleRootOfMinister[minister] = minusPos;
    val[minusPos]--;
  }
  for(int i = 0; i < T[pos].sz; ++i) {
    int ch = T[pos].ptr[i];
    if(onDFSStack[ch])
      continue;
    setNegativeValueDFS(ch);
  }
  onDFSStack[pos] = false;
  DFSStack.sz--;
}
void setNegativeRootValues(){
  for(int i = 0; i < m; ++i) {
    val[possibleRootOfMinister[i]]--;
  }
}
int findTargetEdgeDFS(int pos, int edgeID){
  onDFSStack[pos] = true;
  int myVal = val[pos];
  for(int i = 0; i < T[pos].sz; ++i){
    int ch = T[pos].ptr[i];
    int chID = ID[pos].ptr[i];
    if(onDFSStack[ch])
      continue;
    myVal += findTargetEdgeDFS(ch, chID);
  }
  if(myVal >= k)
    importantTracks.ptr = pushback(importantTracks.ptr, &importantTracks.sz, edgeID);
  onDFSStack[pos] = false;
  return myVal;
}
int main(){
  initialize();
  prePostDFS(0);
  importantCityDFS(0);
  setPositiveValues();
  setImportantCityList();
  setNegativeValueDFS(0);
  setNegativeRootValues();
  int dummy = findTargetEdgeDFS(0, -1);
  qsort(importantTracks.ptr, importantTracks.sz, sizeof(int), cmp);
  printf("%d\n", importantTracks.sz);
  for(int i = 0; i + 1 < importantTracks.sz; ++i) {
    printf("%d ", importantTracks.ptr[i]);
  }
  if(importantTracks.sz != 0) {
    printf("%d\n", importantTracks.ptr[importantTracks.sz-1]);
  }
  return 0;
}
