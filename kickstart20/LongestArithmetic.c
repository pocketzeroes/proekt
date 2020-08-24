#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
  int T;
  scanf("%d", &T);
  for(int case_num=1; case_num<=T; case_num++){
    int N;
    scanf("%d", &N);
    ll A[N];
    for(int z=0; z<N; z++)
      scanf("%lld", &A[z]);
    ll D[N-1];
    for(int i=0; i+1<N; i++)
      D[i] = A[i+1] - A[i];
    int ans = 1;
    int cur = 1;
    for(int i=1; i<N-1; i++){
      if(D[i] == D[i-1])
        cur++;
      else
        cur = 1;
      ans = fmax(ans, cur);
    }
    printf("Case #%d: %d\n", case_num, ans+1);
  }
  return 0;
}
