#include<stdio.h>
int Case,n,i,x,y;
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(i=1;i<n;i++)
      scanf("%d%d",&x,&y);
    puts(n&1?"Alice":"Bob");
  }
  return 0;
}
