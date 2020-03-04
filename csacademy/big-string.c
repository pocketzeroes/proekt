#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
typedef long long ll;
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  char*s=getstr();
  int slen=strlen(s);
  int k;
  scanf("%d", &k);
  ll am[26]; clr(am);
  for(int z=0;s[z];z++){char x=s[z];
    am[x-'a']++;
  }
  fore(i,0,k){
    ll my[26]; memcpy(my, am, sizeof(my));
    fore(j,0,26)
      my[j]+=am[j];
    if(i==0)
      my[s[slen-1]-'a']--;
    else
      my[s[0]-'a']--;
    memcpy(am, my, sizeof(am));
  }
  for(int z=0;z<26;z++){ll x=am[z];
    printf("%lld ", x);
  }
  puts("");
  return 0;
}
