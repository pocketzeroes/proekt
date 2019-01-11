#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}


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

int n,m;
int a[100005];
int b[100005];
int solve=0,now=0;
int maks[100005];
vec risan;

int main(){
  scanf("%d %d", &n, &m);
  for(int i=0; i<n; ++i)
    scanf("%d", &a[i]);
  for(int i=0; i<n; ++i){
    if (now + a[i] > m)
      break;
    now += a[i];
    ++solve;
  }
  if (solve == 0){
    puts("-1");
    return 0;
  }
  for(int i=0; i<n; ++i)
    scanf("%d", &b[i]);
  maks[solve-1] = b[solve-1];
  for(int i=solve-2; i>=0; --i)
    maks[i] = max(maks[i+1], b[i]);
  now       = 0;
  int lasta = 0;
  int nowa  = 0;
  int balon = 0;
  for(int i=0; i<solve; ++i){
    now += b[i];
    if(now > m){
      printf("%d\n", risan.sz);
      for(int i=0; i<risan.sz; ++i)
        printf("%d ", risan.ptr[i]);
      puts("");
      return 0;
    }
    while(nowa < n && lasta + a[nowa] <= now){
      lasta += a[nowa];
      ++balon;
      ++nowa;
    }
    if(maks[i] == b[i] && balon > 0){
      risan.ptr = pushback(risan.ptr, &risan.sz, now);
      --balon;
      --i;
    }
    else
      continue;
  }
  puts("-1");
  return 0;
}
