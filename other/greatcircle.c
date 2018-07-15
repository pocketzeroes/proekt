#include<stdio.h>
#include<math.h>
#define y1 Y1

double lat1, long1, lat2, long2, x1,y1,z1,x2,y2,z2;
double alpha, delta, x, y, z, norm, bestx, besty, bestz;


void try(double a){
   if (a < 0 || a > 1) 
       return;
   x = x1 * a + x2 * (1-a);
   y = y1 * a + y2 * (1-a);
   z = z1 * a + z2 * (1-a);
   norm = sqrt(x*x + y*y + z*z);
   x /= norm;
   y /= norm;
   z /= norm;
   if (x > bestx){
      bestx = x;
      besty = y; 
      bestz = z;
      alpha = a;
   }
}
int main(){
   int i,j,k,m,n,N;
   int deg,sec;
   char dir;
   scanf("%d",&N);
   while (N--) {
      scanf("%d,%d%c",&deg,&sec,&dir);
      lat1 = deg + sec / 60.0;
      if (dir == 'S')
          lat1 = -lat1;
      scanf("%d,%d%c",&deg,&sec,&dir);
      long1 = deg + sec / 60.0;
      if (dir == 'W')
          long1 = -long1;
      scanf("%d,%d%c",&deg,&sec,&dir);
      lat2 = deg + sec / 60.0;
      if (dir == 'S')
          lat2 = -lat2;
      scanf("%d,%d%c",&deg,&sec,&dir);
      long2 = deg + sec / 60.0;
      if (dir == 'W')
          long2 = -long2;
      if (lat1 == -lat2 && fabs(long1-long2) == 180) {
         printf("undefined\n");
         continue;
      }
      x1 = sin(lat1*M_PI/180);
      y1 = sin(long1*M_PI/180) * cos(lat1*M_PI/180);
      z1 = cos(long1*M_PI/180) * cos(lat1*M_PI/180);
      x2 = sin(lat2*M_PI/180);
      y2 = sin(long2*M_PI/180) * cos(lat2*M_PI/180);
      z2 = cos(long2*M_PI/180) * cos(lat2*M_PI/180);
      bestx = -2;
      try(0);
      try(.5);
      try(1);
      for (delta=.5;delta > .000000000001;delta *= .5) {
         try(alpha+delta);
         try(alpha-delta);
      }
      if (bestx >= 0) {
         i = floor(asin(bestx)*180/M_PI*60+.5);
         printf("%d,%dN\n",i/60,i%60);
      }
      else {
         i = floor(asin(-bestx)*180/M_PI*60+.5);
         printf("%d,%dS\n",i/60,i%60);
      }
   }
   return 0;
}
