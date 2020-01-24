#include <stdio.h>
#include <assert.h>
#include <math.h>

#define dt 0.00005
#define g 9.81

int main () {
  while (1) {
    double k, l, s, w;
    scanf("%lf%lf%lf%lf",&k,&l,&s,&w);
    if (k == 0) break;
    assert(0 <= k && 0 <= l && 0 <= s && s < 200 && 0 <= w);
    double d = s<l?s:l, a, f, F = g*w, t = sqrt(2*d/g), v = g*t;
    int click = 0;
    while (1) {
      if (d >= s) {
	if (v > 10) 
	  printf("Killed by the impact.\n");
	if (v < 10) 
	  printf("James Bond survives.\n");
	break;
      }
      if ( v < 0) {
	printf("Stuck in the air.\n");
	break;
      }
      f = F-k*(d<l?0:d-l);
      a = f/w;
      d += v*dt+dt*dt*a/2;
      v += dt*a;
      click++;
    }
  }
}
