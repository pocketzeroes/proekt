#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define cube(x) ((__int128)(x)*(__int128)(x)*(__int128)(x))
typedef long long ll;

typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
typedef struct{
  pair first;
  pair second;
}quad;
quad newQuad(pair a, pair b){
  quad rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
quad*pushbackQ(quad*array, int *size, quad value){
  quad*output = resizeArray(array, quad, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	quad*ptr;
	int sz;
}vecq;
vecq newVecQ(){
	vecq rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////
long size;
int k;
long x[120];
long y[120];
long b[120];
//quad = {pll, pll}
vecq rect;//of quad

int main(){
    scanf("%ld %d", &size, &k);
    for(int i=0; i<k; ++i)
        scanf("%ld%ld%ld", &x[i], &y[i], &b[i]);
    rect.ptr = pushbackQ(rect.ptr, &rect.sz, newQuad(newPair(0, 0), newPair(size, size)));
    long tot = 0;
    while(rect.sz>0){
        quad item   = rect.ptr[rect.sz-1];
        long left   = item.first.first;
        long top    = item.first.second;
        long right  = item.second.first;
        long bottom = item.second.second;
        rect.sz--;
        bool overlap = false;
        bool cover   = false;
        for(int i = 0; i < k; ++i){
            long test_x = x[i];
            if (test_x < left)
                test_x = left;
            if (test_x > right)
                test_x = right;
            long test_y = y[i];
            if (test_y < top)
                test_y = top;
            if (test_y > bottom)
                test_y = bottom;
            if (cube(labs(test_x - x[i])) + cube(labs(test_y - y[i])) <= b[i]){
                if(cube(labs(left  - x[i])) + cube(labs(top    - y[i])) <= b[i] &&
                   cube(labs(right - x[i])) + cube(labs(top    - y[i])) <= b[i] &&
                   cube(labs(left  - x[i])) + cube(labs(bottom - y[i])) <= b[i] &&
                   cube(labs(right - x[i])) + cube(labs(bottom - y[i])) <= b[i]   ){
                    cover = true;
                    break;
                }
                overlap = true;
                break;
            }
        }
        if (cover)
           ;
        else if(overlap){
            if(right - left > bottom - top){
                long mid_x = (left + right) / 2;
                rect.ptr = pushbackQ(rect.ptr, &rect.sz, newQuad(newPair(left, top     ),newPair(mid_x, bottom)));
                rect.ptr = pushbackQ(rect.ptr, &rect.sz, newQuad(newPair(mid_x + 1, top),newPair(right, bottom)));
            }
            else {
                long mid_y = (top + bottom) / 2;
                rect.ptr = pushbackQ(rect.ptr, &rect.sz, newQuad(newPair(left, top),     newPair(right, mid_y )));
                rect.ptr = pushbackQ(rect.ptr, &rect.sz, newQuad(newPair(left, mid_y+1), newPair(right, bottom)));
            }
        }
        else
            tot += (right - left + 1) * (bottom - top + 1);
    }
    printf("%ld\n", tot);
    return 0;
}
