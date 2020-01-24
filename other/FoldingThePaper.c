#include <stdio.h>
enum{ MAXN = 1000000};
int Paper[MAXN];
int PagePos[MAXN];
int N;

void Read1DataSet(){
  int i,a;
  scanf("%d",&N);
  for(i=0; i<N; i++){
    scanf("%d", &a);
    Paper[i]=a;
    PagePos[a]=i;
  }
}
int PossibleToFold(){
  int Stk[2][MAXN];
  int h[2]={0,0};
  int i,n,s;
  for(i=1;i<=N;i++){
    s=PagePos[i]&1;
    if(PagePos[i]<N-1){
      n=Paper[PagePos[i]+1];
      if(n<i){
        if(Stk[s][--h[s]]!=i)
          return 0;
      }
      else
        Stk[s][h[s]++]=n;
    }
    if(PagePos[i]>0){
      s=1-s;
      n=Paper[PagePos[i]-1];
      if(n<i){
        if(Stk[s][--h[s]]!=i)
          return 0;
      }
      else
        Stk[s][h[s]++]=n;
    }
  }
  if(h[0]||h[1]){
    fprintf(stderr,"something is wrong !!!");
    fprintf(stderr,"%d\n",N);
    for(i=0;i>N;i++)
      fprintf(stderr,"%d ",Paper[i]);
    fprintf(stderr,"\n\n");
  }
  return 1;
}
int main(){
  int K=1;
//  scanf("%d ",&K);
  while(K--){
    Read1DataSet();
    if(PossibleToFold())
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
