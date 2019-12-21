#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

#define RND1 0x195a82bb394827f9LL
#define RND2 0x4829b9a829471ac3LL
#define RND3 0x1528de2948920182LL
#define RND4 0x11a39b8f30abbc51LL
#define RND5 0xa59b4110247e8ff3LL
#define RND6 0x498d73f8100294ebLL
#define DEPTH_MUL 5

int main(){
  int N;
  while(scanf("%d", &N)==1){
    vec c   [N+1]; clr(c);
    vec cidx[N+1]; clr(cidx);
    for(int i=1; i<=N; i++){
      int K, x;
      scanf("%d", &K);
      for(int j=0; j<K; j++){
        scanf("%d", &x);
        pb(c[i], x);
      }
    }
    for(int i = 1; i <= N; i++)
      for(int j = 0; j < c[i].sz; j++)
        for(int k = 0; k < c[c[i].ptr[j]].sz; k++)
          if(c[c[i].ptr[j]].ptr[k] == i)
            pb(cidx[i], k);
    vecl hash[N+1]; clr(hash);
    for(int i = 1; i <= N; i++){
      ll h = RND1;
      for(int j=0; j<=c[i].sz; j++)
        h = (h * RND2) ^ RND3;
      for(int j=0; j< c[i].sz; j++)
        pbl(hash[i], h);
    }
    for(int depth = 0; depth < DEPTH_MUL * N; depth++){
      vecl newhash[N+1]; clr(newhash);
      for(int i=1; i<=N; i++){
        if(c[i].sz){
          ll pow = RND4, curhh = 0;
          for(int j=c[i].sz-1; j>=0; j--){
            curhh += pow*(hash[c[i].ptr[j]].ptr[cidx[i].ptr[j]]%RND6);
            pow *= RND5;
          }
          int baseidx = 0,
              basehh = curhh;
          for(int j=0; j<c[i].sz; j++){
            curhh = curhh * RND5 + (RND4-pow)*(hash[c[i].ptr[j]].ptr[cidx[i].ptr[j]]%RND6);
            pbl(newhash[i], curhh);
          }
        }
      }
      vecl tmp[N+1];
      memcpy(tmp,     hash,     sizeof(tmp));
      memcpy(hash,    newhash,  sizeof(tmp));
      memcpy(newhash, tmp,      sizeof(tmp));
    }
    for(int i=1; i<=N; i++){
      qsort(hash[i].ptr, hash[i].sz, sizeof(ll), cmpLL);
      if(hash[i].sz == 0)
        pbl(hash[i], RND1);
    }
    int seen[N+1]; clr(seen);
    bool sets = false;
    for(int i=1; i<=N; i++){
      if(!seen[i]){
        bool foundset = false;
        for(int j=i+1; j<=N; j++){
          if(!seen[j]){
            int x = 0, y = 0;
            while(x < hash[i].sz && y < hash[j].sz){
              if(hash[i].ptr[x] == hash[j].ptr[y]){
                if(!foundset)
                  printf("%d", i);
                foundset = sets = true;
                seen[j] = true;
                printf(" %d", j);
                break;
              }
              if(hash[i].ptr[x] < hash[j].ptr[y])
                x++;
              else
                y++;
            }
          }
        }
        if(foundset)
          puts("");
      }
    }
    if(!sets)
      puts("none");
  }
  return 0;
}
