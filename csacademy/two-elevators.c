#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 300005};
int n,m,e1,e2,a[MAXN],b[MAXN],c[MAXN];

int read(){
  int x;
  scanf("%d", &x);
  return x;
}
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
int main(){
  n=read(); e1=read(); e2=read();
  for(int i=1; i<=n; ++i){ a[i]=read(); b[i]=read(); }
  for(int i=0; i<=3; ++i)c[i]=0;
  for(int i=1; i<=n; ++i){
    if(e1<=a[i]&&a[i]<b[i]||e2<=a[i]&&a[i]<b[i]) c[0]++;
    if(e1<=a[i]&&a[i]<b[i]||e2>=a[i]&&a[i]>b[i]) c[1]++;
    if(e1>=a[i]&&a[i]>b[i]||e2<=a[i]&&a[i]<b[i]) c[2]++;
    if(e1>=a[i]&&a[i]>b[i]||e2>=a[i]&&a[i]>b[i]) c[3]++;
  }
  printf("%d\n", max_element(c, 4));
  return 0;
}
