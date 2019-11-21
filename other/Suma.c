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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

///////////////////////////////
typedef long long ll;
enum{ MAXN = 710};
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

typedef struct{//evt
  int y1, x1, y2, x2, k, l;
}event;

int cmpE(const void*pa, const void*pb){
  event*A=(event*)pa;
  event*B=(event*)pb;
  return((ll)A->l*B->k < (ll)B->l*A->k)?-1:1;
}

typedef struct{//chg
  pair B, old_dad, A;
  int old_size;
}change;
change newchange(pair p1, pair p2, pair p3, int i1){
  return(change){p1, p2, p3, i1};
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
#define pb(zpv, zvv) zpv.ptr = pushbackC(zpv.ptr, &zpv.sz, zvv)
change*pushbackC(change*array, int *size, change value){
  change*output = resizeArray(array, change, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	change*ptr;
	int sz;
}vecc;
vecc newVecC(){
	vecc rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

void Swap(change*nums, int i, int j){
  change t= nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(change*nums, int start, int end){
  while(start < end){
    Swap(nums, start, end);
    start++;
    end  --;
  }
}


int n;
int l[MAXN][MAXN];
int k[MAXN][MAXN];
event*events;
int esz;

// union find
pair dad[MAXN][MAXN];
int  usz[MAXN][MAXN];
vecc changes;//of change

void union_find(){
  for(int i=0; i<MAXN; ++i){
    for(int j=0; j<MAXN; ++j){
      dad[i][j] = newpair(-1, -1);
      usz[i][j] = 1;
    }
  }
}
pair find_dad(int y, int x, bool permanent){
  if(dad[y][x].first == -1)
    return newpair(y, x);
  pair new_dad = find_dad(dad[y][x].first, dad[y][x].second, 1);
  if(permanent == false)
    pb(changes, newchange(newpair(y, x), dad[y][x], newpair(-1, -1), -1));
  return dad[y][x] = new_dad;
}
int merge_sets(int y1, int x1, int y2, int x2, bool permanent){
  pair A = find_dad(y1, x1, permanent);
  pair B = find_dad(y2, x2, permanent);
  if(cmpP(&A, &B)==0)
    return usz[A.first][A.second];
  if(usz[A.first][A.second] < usz[B.first][B.second])
    swap(A, B);
  if(permanent == false)
    pb(changes, newchange(B, dad[B.first][B.second], A, usz[A.first][A.second]));
  usz[A.first][A.second] += usz[B.first][B.second];
  dad[B.first][B.second] = A;
  return usz[A.first][A.second];
}
void restore(){
  reverse(changes.ptr, 0, changes.sz-1);
  for(int z=0; z<changes.sz; z++){change c = changes.ptr[z];
    dad[c.B.first][c.B.second] = c.old_dad;
    if(c.A.first != -1)
      usz[c.A.first][c.A.second] = c.old_size;
  }
  changes.sz=0;
}
//

void process_neighbours(int y1, int x1, int y2, int x2){
  if(y2<0 || y2>=n || x2<0 || x2>=n)
    return;
  int k_diff = k[y2][x2] - k[y1][x1];
  int l_diff = l[y1][x1] - l[y2][x2];
  if(k_diff == 0){
    if(l_diff == 0)
      merge_sets(y1, x1, y2, x2, true);
    return;
  }
  if(k_diff < 0){
    l_diff = -l_diff;
    k_diff = -k_diff;
  }
  if(l_diff < 0)
    return;
  events[esz++] = (event){y1, x1, y2, x2, k_diff, l_diff};
}
int main(){
  union_find();
  scanf("%d", &n);
  int events_sz = n*n*2;
  events = calloc(events_sz, sizeof(event));
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      scanf("%d", l[i]+j);
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      scanf("%d", k[i]+j);
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      for(int d=0; d<2; ++d)
        process_neighbours(i, j, i+dy[d], j+dx[d]);
  int ans=0;
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      find_dad(i, j, 1);
      ans = fmax(ans, usz[i][j]);
    }
  }
  qsort(events, events_sz, sizeof(event), cmpE);
  for(int i=0; i<events_sz; ++i){
    event e = events[i];
    ans = fmax(ans, merge_sets(e.y1, e.x1, e.y2, e.x2, false));
    if(i + 1 == events_sz || cmpE(&e, &events[i+1])<0)
      restore();
  }
  printf("%d\n", ans);
  return 0;
}
