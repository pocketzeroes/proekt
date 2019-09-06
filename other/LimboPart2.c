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
  long long R, C, W, H, v;
  bool d;
  Read(&T);
  while(T--){
    scanf("%lld%lld", &R, &C);
    if ((!R) && (!C)){
      printf("0\n");
      continue;
    }
    W = H = 1;
    d = 0;
    while ((R >= H) || (C >= W)) {
      if (!d)
        W *= 2;
      else
        H *= 2;
      d = !d;
    }
    v = W * H / 2;
    if (d) {
      W /= 2;
      C -= W;
      v += C * H + R;
    } 
    else {
      H /= 2;
      R -= H;
      v += R * W + C;
    }
    printf("%lld\n", v);
  }
  return (0);
}
