#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
void chkmin(ll*a, ll b){
   if(*a > b)
      *a = b;
}
enum{ mn=54};
char*s;
ll f[mn][mn];

int main() {
   s=getstr();
   ll n = strlen(s);
   for (ll y=0;y<=26;y++)
      f[0][y]=y;
   for (ll x=0;x<n;x++){
      ll c=s[x]-'a';
      for (ll y=0;y<=26;y++)
         f[x+1][y]=f[x][y];
      chkmin(&f[x+1][c+1], f[x][c]);
      for (ll y=1;y<=26;y++)
         chkmin(&f[x+1][y], f[x+1][y-1]+1);
   }
   printf("%lld\n", f[n][26]);
   return 0;
}
