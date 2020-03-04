#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

int main(){
  int n,ans=0;
  scanf("%d", &n);
  int a[n];
  int b[3]={1,2,3};
  int pos=0;
  fore(i,0,n){
    scanf("%d", &a[i]);
    if(a[i]==b[pos])
      ans++,pos=(pos+1)%3;
  }
  printf("%d\n", ans);
  return 0;
}
