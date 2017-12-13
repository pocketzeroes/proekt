#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
enum{ MAXN = (int)5e5+228};

int n, a[MAXN];
int res1, res2;

int main(){
  scanf("%d", &n);
  for(int i=1; i<=n+n; ++i){
    scanf("%d", &a[i]);
    if(i & 1){
      if(a[i] != 1) res1++;
      if(a[i] != 0) res2++;
    }
    else{
      if(a[i] != 1) res2++;
      if(a[i] != 0) res1++;
    }
  }
  printf("%d\n", min(res1, res2) / 2);
  return 0;
}
