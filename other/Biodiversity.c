#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{MAXN = 300005};
int n;
char*s[MAXN];
char buf[69];

int count(char*spiv){
  int rv=0;
  for(int i=0;i<n;i++)
    if(strcmp(s[i], spiv)==0)
      rv++;
  return rv;
}
int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%s", buf);
    s[i] = strdup(buf);
  }
  int piv = 0;
  int cnt = 1;
  for(int i=1; i<n; i++){
    if(strcmp(s[piv], s[i])==0)
      cnt++;
    else{
      cnt--;
      if(cnt==0)
        piv = i + 1;
    }
  }
  char*ans = strdup("NONE");
  if(cnt != 0){
    cnt = count(s[piv]);
    if(cnt > n - cnt)
      ans = s[piv];
  }
  puts(ans);
  return 0;
}
