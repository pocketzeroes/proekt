#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
      
typedef long long ll;
typedef long double ld;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct pair{
  ld  first;
  int second;
}pair;
pair newPair(ld a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}
///////////////////




enum{ mn = 50};
ld f[2][mn];
ld vp[mn][mn];
bool h[mn][mn];

bool chkmax(ld*a, ld b){
  if(*a < b){
    *a = b;
    return true;
  }
  return false; 
}
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  for(int i=0; i<m; i++){
    int x,y,p;
    scanf("%d%d%d", &x, &y, &p);
    x--; y--;
    vp[x][y] = p/100.0L;
    h [x][y] = 1;
  }
  int cur=0, nxt=1;
  f[cur][n-1] = 1;
  ld final = 0;
  ld prev = 0;
  for (int k=0;k<20000;k++) {
    f[cur][n-1] = 1;
    bool ch = 0;
    for (int x=n-2;x>=0;x--){
      vecp v = newVecP();
      for (int y=0;y<n;y++){
        if (h[x][y])
          v.ptr = pushbackP(v.ptr, &v.sz, newPair(-f[cur][y], y));
      }
      qsort(v.ptr, v.sz, sizeof(pair), cmpP);
      ld all=1;
      ld ans=0;
      for(int z=0;z<v.sz;z++){pair w=v.ptr[z];
        ld contrib = -w.first;
        int y      = w.second;
        ld p = vp[x][y];
        ld pp = all*p;
        ans += pp*contrib;
        all *= (1-p);
      }
      f[nxt][x] = ans;
      if (fabs(ans-f[cur][x])>1e-12) 
        ch=1;
    }
    ld have = f[nxt][0];
    chkmax(&final, have);
    if (!ch) 
      break;
    swap(cur, nxt);
  }
  printf("%.16f\n", (double)final);
}






