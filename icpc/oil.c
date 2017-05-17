#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct tripS
{
    int first ;
    int second;
    int third ;
}trip;
trip newTrip(int _x, int _y, int _z)
{
    trip rez;
    rez.first =_x;
    rez.second=_y;
    rez.third =_z;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}

/////
int slopecmp(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  long long av = (long long)a->second * b->third;
  long long bv = (long long)b->second * a->third;
  if (av != bv)
    return(av < bv)?-1:1;
  return(a->first > b->first)?-1:1;
}
int main(){
  int N;
  scanf("%d", &N);
  do{
    int x1[N];
    int x2[N];
    int y [N];
    for(int i = 0; i < N; i++){
      scanf("%d %d %d", &x1[i], &x2[i], &y[i]);
      if(x1[i] > x2[i])
        SWAP(x1[i], x2[i]);
    }
    int ret = 0;
    for (int i = 0; i < N; i++){
      trip*v=NULL;
      int  vSz=0;
      int cur = 0;
      for(int j = 0; j < N; j++){
        if(y[j] == y[i]){
          if(x1[i] >= x1[j] && x1[i] <= x2[j]){
            cur += x2[j]-x1[j];
          }
        }
        else if(y[j] < y[i]){
          v=pushbackT(v, &vSz, newTrip(x2[j]-x1[j], x1[i]-x2[j], y[i]-y[j]));
          v=pushbackT(v, &vSz, newTrip(x1[j]-x2[j], x1[i]-x1[j], y[i]-y[j]));
        }
        else{
          v=pushbackT(v, &vSz, newTrip(x2[j]-x1[j], x1[j]-x1[i], y[j]-y[i]));
          v=pushbackT(v, &vSz, newTrip(x1[j]-x2[j], x2[j]-x1[i], y[j]-y[i]));
        }
      }
      qsort(v, vSz, sizeof(trip), slopecmp);
      ret = max(ret, cur);
      for(int j = 0; j < vSz; j++){
        cur += v[j].first;
        ret = max(ret, cur);
      }
    }
    printf("%d\n", ret);
  }while(0);
}





















































