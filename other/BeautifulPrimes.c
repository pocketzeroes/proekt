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
  int i,j,p;
  long double v;
  Read(&T);
  while (T--){
   Read(&N);
    for (i=0; i<N+1; i++){
     v=0;
      for (j=0; j<N; j++){
       p=j<i ? 2 : 11;
       v+=log10((long double)p);
      }
      if (v<N-0.1){
        for (j=0; j<N; j++){
         p=j<i ? 2 : 11;
         printf("%d%c",p,j==N-1 ? '\n' : ' ');
        }
       break;
      }
    }
  }
  return 0;
}
