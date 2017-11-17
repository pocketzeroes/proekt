#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
char buff[200000];
int main(){
  ll n, m = 0LL;
  char*a;
  char*b;
  scanf("%lld", &n);
  scanf("%s", &buff); a = strdup(buff);
  scanf("%s", &buff); b = strdup(buff);
  for (int i=1; i<n; i++)
    a[i]^=(a[i-1]=='1'), b[i]^=(b[i-1]=='1');
  for (int i=0; i<n; i++){
    m *= 2;
    m += (a[i]-b[i]);
  }
  printf("%lld\n", labs(m)-1);
}
