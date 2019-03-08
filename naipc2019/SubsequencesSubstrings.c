#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int main(){
  char*s = getstr();
  char*t = getstr();
  int n = strlen(s),
      m = strlen(t);
  int next[n+2][26];
  for(int i=0; i<n+2; i++)
    fill(next[i], 26, n);
  for(int i=n-1; i>=0; i--){
    for(int j=0; j<26; j++)
      next[i][j] = next[i+1][j];
    next[i][s[i]-'a'] = i;
  }
  ll ans = 0;
  for(int L=0; L<n; L++){
    int R = L;
    for(int idx=0; idx<m; R=next[R][t[idx++]-'a']+1);
    ans += (n+1)-R;
  }
  printf("%lld\n", ans);
  return 0;
}
