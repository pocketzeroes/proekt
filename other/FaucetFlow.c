#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

#define swap(a,b) do\
  {\
    a ^= b;\
    b ^= a;\
    a ^= b;\
  } while (0)
void Swap(ll*nums, ll i, ll j){
  ll t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void reverse(ll*nums,ll start,ll end){
  while( start < end) {
    Swap(nums, start, end);
    start++;
    end  --;
  }
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll *pushback(ll *array, ll *size, ll value) {
  ll *output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ll*ptr;
	ll sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int main(){
  ll leftx, rightx;
  ll lefth, righth;
  ll leftt, rightt, midt, midl, midr;
  ll i, j, x;
  for(;;){
    scanf("%lld %lld", &leftx, &rightx);
    if( leftx == 0 && rightx == 0)
      break;
    vec div = newVec();
    for( i = leftx; i <= rightx; i += 2){
      scanf("%lld", &x );
      div.ptr = pushback(div.ptr, &div.sz, x);
    }
    lefth = righth = 0;
    for( i = leftx, j = 0; i < 0; i += 2, j++)
      lefth = max(lefth, div.ptr[j]);
    for( i = rightx, j=div.sz-1; i > 0; i -= 2, j--)
      righth = max(righth, div.ptr[j]);
    if( lefth > righth){
      reverse(div.ptr, 0, div.sz-1);
      swap(lefth, righth);
      swap(leftx, rightx);
      leftx = -leftx;
      rightx = -rightx;
    }
    leftt = lefth = 0;
    for( i = leftx, j = 0; i < 0; i += 2, j++){
      lefth = max(lefth, div.ptr[j]);
      leftt += 2*lefth;
    }
    midl = j-1; midr = j;
    midt = 2*lefth;
    leftt -= 2*lefth;
    while( div.ptr[midl] < lefth){
      midl--;
      midt  += 2*lefth;
      leftt -= 2*lefth;
    }
    while( div.ptr[midr] < lefth){
      midr++;
      midt += 2*lefth;
    }
    if( lefth == righth){
      rightt = righth = 0;
      for( i = rightx, j = div.sz-1; j > midr; i -= 2, j-- ){
        righth = max(righth, div.ptr[j]);
        rightt += 2*righth;
      }
			printf( "%lld\n", 2* min(leftt, rightt) + midt );
		}
    else {
      rightt = 0;
      for( j = midr; div.ptr[j] <= lefth; j++)
        rightt += 2*lefth;
      printf( "%lld\n", leftt + midt + min(leftt, rightt) );
    }
  }
  return 0;
}
