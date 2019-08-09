#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

double TWOPI = M_PI + M_PI;
double SQRT3OVER4 = 0.4330127018922193;
double EPSILON = 0.00001;
double a, b, c;

double angle( double a, double b, double c ){
    double angle = 0.0;
    if( fabs(c-a-b)<EPSILON )
        angle = M_PI;
    else if( fabs(fabs(a-b)-c)<EPSILON )
        angle = 0.0;
    else
        angle = acos( (a*a+b*b-c*c)/(2.0*a*b) );
    while( angle<0.0 )
        angle += TWOPI;
    return angle;
}
double heron( double a, double b, double c ){
    double s = (a+b+c)/2.0;
    return sqrt( s*(s-a)*(s-b)*(s-c) );
}
double f( double x ){
    return angle( a, b, x ) + angle( a, c, x ) + angle( b, c, x ) - TWOPI;
}
int main(){
    a = in_nextDouble();
    b = in_nextDouble();
    c = in_nextDouble();
    double dab = fabs( a-b );
    double dac = fabs( a-c );
    double dbc = fabs( b-c );
    double lo = fmax( fmax( dab, dac ), dbc );
    double hi = fmin( fmin( a+b, a+c ), b+c );
    double area = -1.0;
    if( lo<=hi ){
        if( lo<=hi+EPSILON && f(lo)*f(hi)<=EPSILON ){
            while( hi-lo > 0.000000001 ){
                double mid = (lo+hi)/2.0;
                if( f(mid)<0.0 )
                    lo=mid;
                else
                    hi=mid;
            }
            area = lo*hi*SQRT3OVER4;
        }
    }
    printf("%.9lf\n", area);
    return 0;
}
