#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;

int main(){
  ll n;
  scanf("%lld", &n);
  ll a[n];
  for(int i=0;i<n;i++)
    scanf("%lld", &a[i]);
  double ans=0;
  for(ll i=0;i<n;i++){
    if(!a[i])
      a[i]=-1;
    else
      a[i]*=-2;
  }
  for(ll i=0;i<n;i++){
    if(a[i]>0){
      ll j=i+1;
      ll cumsum=a[i];
      while(j<n&&cumsum>=0)
        cumsum+=a[j],j++;
      if(cumsum>=0)
        ans=max(ans,1.0*(j-i));
      if(cumsum==-1&&a[j-1]==-2)
        ans=max(ans,(j-i)-0.5);
      else
        ans=max(ans,1.0*(j-i-1));
      i=j-1;
    }
  }
  printf("%lf\n", ans);
  return 0;
}
