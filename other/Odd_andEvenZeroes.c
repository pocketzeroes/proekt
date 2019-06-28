#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll ans, sum, t, n, k, m, cnt[100], change[100], tag, id, tmp;
int dx[] = {0,1,-1,0,0};
int dy[] = {0,0,0,1,-1};

int main(){
  cnt[0] = 1; change[0] = 0;
  cnt[1] = 5; change[1] = 1;
  tag = 0; id = 2; tmp = 5;
  while(1){
    if(tmp > (1e17))
      break;
    tag = 0;
    for(int i=1;i<=5;i++){
      if(!tag)
        cnt[id] += cnt[id-1];
      else
        cnt[id] += tmp-cnt[id-1];
      if(change[id-1])
        tag = (tag+1)%2;
    }
    tmp *= 5;
    tag = (tag+1)%2;
    change[id] = tag;
    id++;
  }
  while(1){
    ans = 0;
    scanf("%lld",&n);
    if(n == -1)
      break;
    tag = 0;
    while(1){
      tmp = 1; id = 0;
      while(tmp*5 <= n){
        tmp *= 5; id++;
      }
      if(!tag)
        ans += cnt[id];
      else
        ans += tmp-cnt[id];
      if (change[id]){
        tag = (tag + 1) % 2;
      }
      n -= tmp;
      if (n == -1)
        break;
    }
    printf("%lld\n",ans);
  }
  return 0;
}
