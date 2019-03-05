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
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int upper_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x >= a[mid])
      l = mid + 1;
    else
      h = mid;
  }
  return l;
}
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}
int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

//////////////////

typedef struct{
  int turn, info, a, b;
}Result;
Result newResult(int _turn, int _info, int _a, int _b){
  Result rez;
  rez.turn = _turn; 
  rez.info = _info; 
  rez.a    = _a; 
  rez.b    = _b;
  return rez;
}
  
enum{ MAX = 10};
char*WIN = "E";

typedef struct{
  int length;
  vec matches[2*MAX][MAX][MAX];
}Solver;
Solver solver[MAX];

Result matchResult(Solver*s, int mask){
  int sa = 0, sb = 0;
  int na = s->length,
      nb = s->length;
  int j = 2 * s->length;
  for(int i = 0, _n = (s->length * 2); i < _n; i++){
    j--;
    if (i % 2 == 0) {
      na--;
      if ((((mask) >> (j)) & 1))
        sa++;
    }
    else {
      nb--;
      if ((((mask) >> (j)) & 1))
        sb++;
    }
    int subMatch = mask >> j;
    if (sa > sb + nb)
      return newResult(i + 1, subMatch, sa, sb);
    if (sb > sa + na)
      return newResult(i + 1, subMatch, sa, sb);
  }
  return newResult(2 * s->length, mask, sa, sb);
}
void prep(Solver*s){
  for (int mask = 0, _n = ((1LL << (2 * s->length))); mask < _n; mask++){
    Result result = matchResult(s, mask);
    s->matches[result.turn][result.a][result.b].ptr = pushback(s->matches[result.turn][result.a][result.b].ptr, &s->matches[result.turn][result.a][result.b].sz, result.info);
  }
  for(int turn = 0, _n = (2 * s->length + 1); turn < _n; turn++){
    for(int sa = 0, _n = (s->length + 1); sa < _n; sa++){
      for(int sb = 0, _n = (s->length + 1); sb < _n; sb++){
        vec*cur = &s->matches[turn][sa][sb];
        if(cur->sz==0)
          continue;
        qsort(cur->ptr, cur->sz, sizeof(int), cmp);
        cur->sz = unique(cur->ptr, cur->sz);
      }
    }
  }
}
bool onlyMatch(Solver*s, int turn, int sa, int sb, int subMatch, int subTurn){
  int minMask = subMatch << (turn - subTurn);
  int maxMask = minMask ^ ((1LL << (turn - subTurn)) - 1);
  vec*cur = &s->matches[turn][sa][sb];
  int L = lower_bound(cur->ptr, cur->sz, minMask);
  int R = upper_bound(cur->ptr, cur->sz, maxMask);
  assert(L < R);
  return R - L == 1;
}
Solver newSolver(int len){
  Solver this;
  this.length = len;
  for(int i=0, _n = (2 * len + 1); i < _n; i++) 
    for(int j=0, _n = (len + 1); j < _n; j++) 
      for(int k=0, _n = (len + 1); k < _n; k++)
        this.matches[i][j][k].sz=0;
  prep(&this);
  return this;
}
pair solve(Solver*s, int mask){
  Result result = matchResult(s, mask);
  mask = result.info;
  for(int i = (0), _b = (result.turn); i <= _b; i++){
    int subMatch = mask >> (result.turn - i);
    if(onlyMatch(s, result.turn, result.a, result.b, subMatch, i))
      return newPair(result.turn, i);
  }
  return newPair(result.turn, result.turn);
}
void prepare(){
  for (int i = (1), _b = (10 - 1); i <= _b; i++)
    solver[i] = newSolver(i);
}
void process(){
  int n;
  scanf("%d", &n);
  int mask = 0;
  for(int i = 0, _n = (2 * n); i < _n; i++){
    char input[16];
    scanf("%s", &input);
    mask = (mask << 1) ^ (strcmp(input, WIN)==0);
  }
  pair res = solve(&solver[n], mask);
  printf("%d %d\n", res.first, res.second);
}
int main(){
  prepare();
  int t;
  scanf("%d", &t);
  for(int love=0, _n=(t); love<_n; love++)
    process();
  return 0;
}

