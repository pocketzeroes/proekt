#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

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
////////////////////
enum{ NMAX = 100010};
vecp adia[NMAX];
ll dp[NMAX][2];

void calc_dp(int nod, int tata){
  ll s0 = 0;
  ll difmax1 = 0, 
     difmax2 = 0;
  for(int z=0; z<adia[nod].sz; z++){pair i = adia[nod].ptr[z];
    if(i.first == tata)
      continue;
    calc_dp(i.first, nod);
    dp[i.first][1] += i.second;
    s0    += dp[i.first][0];
    ll dif = dp[i.first][1] - dp[i.first][0];
    if(dif > difmax1)
      difmax2 = difmax1, difmax1 = dif;
    else if(dif > difmax2)
      difmax2 = dif;
  }
  dp[nod][0] = s0 + difmax1 + difmax2;
  dp[nod][1] = s0 + difmax1;
}
int main(){
  int n, a, b, c;
  scanf("%d", &n);
  while(--n){
    scanf("%d %d %d", &a, &b, &c);
    adia[a].ptr = pushbackP(adia[a].ptr, &adia[a].sz, newPair(b, c));
    adia[b].ptr = pushbackP(adia[b].ptr, &adia[b].sz, newPair(a, c));
  }
  calc_dp(1, 0);
  printf("%lld\n", dp[1][0]);
  return 0;
}
