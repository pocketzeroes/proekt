#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int arr[1000100];
int x[100010],y[100010],val[100010];
int l[1000100],r[100010];

int main(){
  int n, q;
  scanf("%d %d", &n, &q);
  for(int i=1; i<=q;i++){
    scanf("%d %d %d", &x[i], &y[i], &val[i]);
    arr[x[i]  ]+=val[i];
    arr[y[i]+1]-=val[i];
  }
  for(int i=1; i<=n;i++){
    arr[i]=arr[i-1]+arr[i];
  }
  int mid=0;
  int maxi=0;
  for(int i=1;i<=n;i++){
    l[i]=max(l[i-1],arr[i]);
    if(arr[i]>maxi){
      maxi=arr[i];
      mid=i;
    }
  }
  for(int i=n;i>=1;i--){
    r[i]=max(r[i+1],arr[i]);  
  }
  int ans = l[n];
  for(int i=1;i<=q;i++){
    int a=x[i];
    int b=y[i];
    int v=val[i];
    if(mid>=a && mid<=b){
      int temp=l[a-1];
      temp=max(temp,r[b+1]);
      temp=max(temp,maxi-v);
      ans=min(ans,temp);
    }
  }
  printf("%d\n", ans);
}
























































