#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmp(const void *b, const void *a){//rev
  return ( *(int*)a - *(int*)b );
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
int cmpP(const void*pb, const void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
///////////////////////////////////

int main(){
  int P, H;
  while(scanf("%d %d", &P, &H)==2){
    int S[P][H+1]; memset(S  , 0, sizeof(S)  );
    ll tot[P];     memset(tot, 0, sizeof(tot));
    for(int i = 0; i < P; i++){
      for(int j = 0; j < H; j++){
        scanf("%d", &S[i][j]);
        tot[i] += S[i][j];
      }
      qsort(S[i], H+1, sizeof(int), cmp); //rev
    }
    for(int i = 0; i < P; i++){
      vecp events = newVecP();
      int cur = 0;
      for(int j = 0; j < P; j++){
        ll itot = tot[i], 
           jtot = tot[j], 
           lim = 1000000000;
        if(jtot <= itot)
          cur++;
        for(int ih = 0, jh = 0; ih < H || jh < H; S[i][ih] > S[j][jh] ? ih++ : jh++){
          bool old = (jtot <= itot);
          int v = max(S[i][ih], S[j][jh]);
          itot -= (lim-v) * ih; jtot -= (lim-v) * jh;
          lim = v;
          if (!old && jtot <= itot)
            events.ptr = pushbackP(events.ptr, &events.sz, newPair(lim+(itot-jtot)/(jh-ih), 1));
          else if (old && jtot > itot)
            events.ptr = pushbackP(events.ptr, &events.sz, newPair(lim+(jtot-itot-1)/(ih-jh), -1));
        }
      }
      qsort(events.ptr, events.sz, sizeof(pair), cmpP);//rev
      int ret = cur;
      for(int z=0;z<events.sz;z++){pair e = events.ptr[z];
        cur += e.second; 
        ret = min(ret, cur);
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}
