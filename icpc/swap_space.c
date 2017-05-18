#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

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
int cmpT(const void*pa, const void*pb)
{
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int diff;
    diff = a->first  - b->first;  if(diff!=0) return diff;
    diff = a->second - b->second; if(diff!=0) return diff;
    return a->third  - b->third;
}

int main(int argc, char**argv){
  int i;
  int N, x, y;
  scanf("%d", &N);
  do{
    trip*v=NULL;
    int vSz=0;
    for(i = 0; i<N; i++){
      scanf("%d %d", &x, &y);
      v = pushbackT(v, &vSz, newTrip( (y>x) ? x:2000000001-y, x, y));
    }
    long long ret = 0, cap = 0;
    qsort(v, vSz, sizeof(trip), cmpT);
    for(i = 0; i < vSz; i++){
      if(cap < v[i].second){
        ret += v[i].second - cap;
        cap  = v[i].second;
      }
      cap += v[i].third - v[i].second;
    }
    printf("%lld\n", ret);
  }while(0);
}






















































