#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;

int pre[13][1<<12][13];

int main(){
  for(int x1=0; x1<=12; x1++)
  for(int b1=0; b1<(1<<12); b1++)
  for(int x2=0; x2<=12; x2++){
    int b2 = b1;
    for(int x3=x1; x3<=x2-2; x3++)
      if(((b2>>x3)&3) == 1)
        b2 -= (1<<x3);
    for(int x3=x1-2; x3>=x2; x3--)
      if(((b2>>x3)&3) == 2)
        b2 -= (2<<x3);
    pre[x1][b1][x2] = b2;
  }
  int N, M, P;
  while(scanf("%d %d %d", &N, &M, &P)==3){
    if(N%2 && M%2)
      puts("1");
    else if(N%2||M%2){
      if(M%2)
        swap(N, M);
      ll ret=1ll;
      for(int i=0; i<N/2; i++)
        ret=(ret*(M/2+1))%P;
      printf("%lld\n", ret);
    }
    else{
      N/=2;
      M/=2;
      ll state[N+1][1<<N]; clr(state);
      state[0][(1<<N)-1]=1;
      for(int i=0; i<=M; i++){
        ll state2[N+1][1<<N]; clr(state2);
        ll tmp   [N+1][1<<N];
        for(int x1=0; x1<=N; x1++)
        for(int b1=0; b1<(1<<N); b1++)
        for(int x2=0; x2<=N; x2++)
          state2[x2][pre[x1][b1][x2]] += state[x1][b1];
        for(int x2=0; x2<=N; x2++)
        for(int bi=1; bi<(1<<N); bi<<=1)
        for(int b2=0; b2<(1<<N); b2++)
          if((b2&bi)==0)
            state2[x2][b2] += state2[x2][b2+bi];
        for(int x2=0; x2<=N; x2++)
        for(int b2=0; b2<(1<<N); b2++)
          state2[x2][b2] %= P;
//      swap(state, state2);
        memcpy(&tmp,    &state,  sizeof(state));
        memcpy(&state,  &state2, sizeof(state));
        memcpy(&state2, &tmp,    sizeof(state));
      }
      printf("%lld\n", state[0][0]);
    }
  }
  return 0;
}
