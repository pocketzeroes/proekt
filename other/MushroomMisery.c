#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{ // Circle
  double x,
         y,
         r;
}Circle;
typedef struct{ // Range
  int min,
      max;
}Range;
#define pb(zpv, zvv) zpv.ptr = pushbackR(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Range*pushbackR(Range*array, int *size, Range value){
  Range*output = resizeArray(array, Range, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Range*ptr;
	int sz;
}vecr;
vecr newVecR(){
	vecr rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int cmp(const void*pa, const void*pb){
  Range*a=(Range*)pa;
  Range*b=(Range*)pb;
  return(a->min < b->min || (a->min == b->min && a->max < b->max))?-1:1;
}
Range getCircleRangeX(Circle c, int y, int size){
  Range r;
  if( y + 1 < c.y && c.y - c.r <= y + 1 ){
    double deltaY = c.y - (y+1);
    double deltaDistance = sqrt( c.r * c.r - deltaY * deltaY );
    r.min = fmax(0, (int)(c.x - deltaDistance));
    r.max = fmin(size-1, (int)(c.x + deltaDistance));
    return r;
  }
  else if( y > c.y && c.y + c.r >= y ){
    double deltaY = y - c.y;
    double deltaDistance = sqrt( c.r * c.r - deltaY * deltaY );
    r.min = fmax(0, (int)(c.x - deltaDistance));
    r.max = fmin(size-1, (int)(c.x + deltaDistance));
    return r;
  }
  else if( c.y >= y && c.y <= y+1 ){
    r.min = fmax(0, (int)(c.x - c.r));
    r.max = fmin(size-1, (int)(c.x + c.r));
    return r;
  }
  else{
    r.min = -1;
    r.max = -1;
    return r;
  }
}
int main(){
  int N=1;
  while(1){
    for(int testCase = 0 ; testCase < N ; ++testCase){
      int size, n;
      scanf("%d %d", &size, &n);
      Circle circles[n];
      for(int i=0; i<n ; ++i){
        Circle c;
        scanf("%lf%lf%lf", &(c.x), &(c.y), &(c.r));
        circles[i] = c;
      }
      int totalAffectedSquares=0;
      for(int i=0; i<size; ++i){
        vecr ranges=newVecR();//of Range
        for(int j=0; j<n; ++j){
          Range range = getCircleRangeX(circles[j], i, size);
          if(range.min != -1 &&
             range.max != -1)
            pb(ranges, range);
        }
        if(ranges.sz > 0){
          qsort(ranges.ptr, ranges.sz, sizeof(Range), cmp);
          Range range = ranges.ptr[0];
          for(int j=1; j<ranges.sz; ++j){
            if(range.max >= ranges.ptr[j].min)
              range.max = fmax( range.max, ranges.ptr[j].max );
            else{
              totalAffectedSquares += range.max - range.min + 1;
              range = ranges.ptr[j];
            }
          }
          totalAffectedSquares += range.max - range.min + 1;
        }
      }
      printf("%d\n", totalAffectedSquares);
    }
    break;
  }
  return 0;
}
