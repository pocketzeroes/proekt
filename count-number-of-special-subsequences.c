#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll from[3];
ll to[3];
const ll mo=1000000007;

int countSpecialSubsequences(int*nums, int numsSz){
  ll from[4]={1,0,0,0};
  for(int z=0;z<numsSz;z++){int n=nums[z];
    ll to[4]={from[0],from[1],from[2],from[3]};
    to[n+1] += from[n]+from[n+1];
    to[n+1] %= mo;
//  swap(from, to);
    ll tmp[4];
    memcpy(&tmp,    &from,   sizeof(from));
    memcpy(&from ,  &to,     sizeof(from));
    memcpy(&to,     &tmp,    sizeof(from));
  }
  return from[3];
}
