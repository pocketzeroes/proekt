#include<stdio.h>
typedef unsigned long long u64;

int hw(u64 x)  { int w = x&1; while(x >>= 1) w += x&1; return w; }
int main(){
  u64 n,x,y;
  int t,w,i,h;
  for ( scanf("%d",&t) ; t ; --t, putchar('\n') )
    for (scanf("%lld %lld %lld %d %d", &n, &x, &y, &w, &h); h; --h, ++y)
      for (i=0; i<w; ++i)
	printf("%d%c", 1-2*(1 & hw((x+i)&y)), (i==w-1) ? '\n' : ' ');
  return 0;
}
