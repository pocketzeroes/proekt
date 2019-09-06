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
 int T;
 Read(&T);
 for(int i = 0; i < T; i++){
  long long L, R;
  scanf("%lld%lld", &L, &R);
  long long d = R + L + 1;
  printf("%lld\n", d*(d-1)/2 + R + 1);
 }
 return(0);
}
