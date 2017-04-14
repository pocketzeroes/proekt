#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void swap(int*nums, int i, int j) {
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
typedef struct pair{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
int cmpRev(const void *b, const void *a)
{
  return ( *(int*)a - *(int*)b );
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushback(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef long long lol;
const int N   =   -1;
const lol  INF =(lol)1e9 + 19;
int n, m;
int**a;

void read(){
  scanf("%d%d", &n, &m);
  a=malloc(n*sizeof(int*));
  for (int i = 0; i < n; i++) {
    a[i]=malloc(m*sizeof(int));
    for (int j = 0; j < m; j++)
      scanf("%d", &a[i][j]);
  }
}
void solve(){
  for (int i = 1; i < n; i++){
    pair*up=NULL;int upSz=0;
    for (int j = 0; j < m; j++)
      up=pushback(up, &upSz, newPair(a[i - 1][j], j));
    qsort(up, upSz, sizeof(pair), cmpP);
    int*down = malloc(m*sizeof(int));
    for(int z=0;z<m;z++)
      down[z]=a[i][z];
    qsort(down, m, sizeof(int), cmpRev);
    int l = m;
    int r = -1;
    for (int j = 0; j < m; j++)
      if (down[j] == up[j].first) {
        l = min(l, j);
        r = max(r, j);
      }
    if (l <= r) {
      int x = down[l];
      int ll = m;
      int rr = -1;
      for (int j = 0; j < m; j++)
        if (down[j] == x || up[j].first == x) {
          ll = min(ll, j);
          rr = max(rr, j);
        }
      ll--;
      rr++;
      for (; l <= r && ll >= 0; ) {
        swap(down, ll, l);
        ll--;
        l++;
      }
      for (; l <= r && rr < m; ) {
        swap(down, l, rr);
        l++;
        rr++;
      }
      if (l <= r) {
        puts("-1");
        return;
      }
    }
    for (int j = 0; j < m; j++)
      a[i][up[j].second] = down[j];
    free(up);
    free(down);
  }
  for(int i = 0; i < n; i++,putchar('\n'))
    for(int j = 0; j < m; j++)
      printf("%d ", a[i][j]);
}
int main(){
  int k = 1;
  for (int tt = 0; tt < k; tt++) {
    read();
    solve();
  }
  return 0;
}





























































