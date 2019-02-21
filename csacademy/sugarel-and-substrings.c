#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int pos[26];
char s[100000];

int main(){
  int N, j=0;
  ll ans = 0;
  scanf("%d %s", &N, &s);
  memset(pos, -1, sizeof(pos));
  for(int i=0; i<N; i++){
    if(pos[s[i]-'a']>=j)
      j = pos[s[i]-'a']+1;
    ans += i-j+1;
    pos[s[i]-'a'] = i;
  }
  printf("%lld\n", ans);
  return 0;
}
