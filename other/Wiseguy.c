#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool Read(int*first){
  char c,r=0,n=0;
 *first=0;
  for(;;){
   c=getchar();
    if ((c<0) && (!r))
     return(0);
    if ((c=='-') && (!r))
     n=1;
    else
    if ((c>='0') && (c<='9'))
    *first = *first * 10+c-'0',r=1;
    else if (r)
     break;
  }
  if (n)
    *first = - *first;
  return 1;
}
int main(){
  int T,N;
  int i,a,b,h3;
  double ans;
  static long double dyn[500 +1][500 +1],sum[500 +1][500 +1];
  dyn[0][0]=dyn[1][0]=1;
  for (i=0; i<500 +1; i++){
   if (i>=2)
    for (a=0; a<i; a++){
     b=i-a-1;
      for (h3=0; h3<i; h3++){
       dyn[i][h3+1]+=dyn[a][h3]*sum[b][h3+1]/i;
       dyn[i][h3+1]+=sum[a][h3]*dyn[b][h3]/i;
      }
    }
   for (a=0; a<500; a++)
    sum[i][a+1]=sum[i][a]+dyn[i][a];
  }
  Read(&T);
  while(T--){
   Read(&N);
   ans=0;
    for (i=0; i<N; i++)
     ans+=i*dyn[N][i];
   printf("%.9lf\n",ans);
  }
  return 0;
}
