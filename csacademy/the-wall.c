#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ mod = 1000000007};
ll x[10][10],y[10][10],v[10][10];

void power(int i)
{
  if(i==1)
  {
      v[0][0]=x[0][0];v[1][0]=x[1][0];v[0][1]=x[0][1];v[1][1]=x[1][1];
      return ;
  }
  power(i/2);
  y[0][0]=(v[0][0]*v[0][0])%mod+(v[0][1]*v[1][0])%mod;
  y[0][1]=(v[0][0]*v[0][1])%mod+(v[0][1]*v[1][1])%mod;
  y[1][0]=(v[0][0]*v[1][0])%mod+(v[1][1]*v[1][0])%mod;
  y[1][1]=(v[0][1]*v[1][0])%mod+(v[1][1]*v[1][1])%mod;
  v[0][0]=y[0][0]%mod;
  v[0][1]=y[0][1]%mod;
  v[1][0]=y[1][0]%mod;
  v[1][1]=y[1][1]%mod;
  if(i%2==1)
  {
      y[0][0]=(v[0][0]*x[0][0])%mod+(v[0][1]*x[1][0])%mod;
      y[0][1]=(v[0][0]*x[0][1])%mod+(v[0][1]*x[1][1])%mod;
      y[1][0]=(x[0][0]*v[1][0])%mod+(v[1][1]*x[1][0])%mod;
      y[1][1]=(x[0][1]*v[1][0])%mod+(x[1][1]*v[1][1])%mod;
      v[0][0]=y[0][0]%mod;
      v[0][1]=y[0][1]%mod;
      v[1][0]=y[1][0]%mod;
      v[1][1]=y[1][1]%mod;
  }
  return ;
}
int main()
{
  int n;
  scanf("%d", &n);
  x[0][0]=16;
  x[0][1]=20;
  x[1][0]=5;
  x[1][1]=6;
  if(n==1){puts("6");return 0;}
  power(n/2);
  if(n%2==0)
  {
    printf("%d\n", v[0][0]);
  }
  else
  {
    ll ans1=v[0][0]*6LL+v[0][1]*2LL;
    ans1%=mod;
    printf("%lld\n", ans1);
  }
}
