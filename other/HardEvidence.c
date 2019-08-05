#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

double GetViewAngle(double px1, double py1, double px2, double py2, double a, double r){
    double qx = cos(a)*r, qy = sin(a)*r;
    double vx1 = qx - px1, vy1 = qy - py1, vx2 = qx - px2, vy2 = qy - py2;
    double d = (vx1 * vx2 + vy1 * vy2) / (sqrt(vx1 * vx1 + vy1 * vy1) * sqrt(vx2 * vx2 + vy2 * vy2));
    double angle = acos(d);
    return angle;
}
double*QuadraticEquation(double a, double b, double c){
    double d = b * b - 4 * a * c;
    if (d < 0)
        return NULL;
    d = sqrt(d);
    double*rv = calloc(2, sizeof(double));
    rv[0]=(-b + d) / (2 * a);
    rv[1]=(-b - d) / (2 * a);
    return rv;
}
int main(){
    int n = in_nextInt(),
        r = in_nextInt();
    double x[n];
    double y[n];
    for (int i = 0; i < n; i++){
        x[i] = in_nextDouble();
        y[i] = in_nextDouble();
    }
    double bestAngle = 0.0, 
           bestX = 0, 
           bestY = 0;
    double start[n];
    double stop [n];
    for(int i = 0; i < n; i++){
        int j = (i + 1)%n;
        double dx = x[j] - x[i], dy = y[j] - y[i];
        double a = dx*dx + dy*dy, b = 2*(dx*x[i] + dy*y[i]), c = x[i]*x[i] + y[i]*y[i] - r*r;
        double*result = QuadraticEquation(a,b,c);
        double px1 = x[i] + result[0]*dx, py1 = y[i] + result[0]*dy;
        double px2 = x[i] + result[1]*dx, py2 = y[i] + result[1]*dy;
        start[i] = atan2(py2, px2);
        stop [i] = atan2(py1, px1);
    }
    for (int i = 0; i < n; i++){
        int t = i;
        while (1){
            double lo = start[t], 
                   hi = stop [i];
            if (hi < lo)
                hi += 2*M_PI;
            double angle = 0.0;
            while (hi - lo > 1e-6){
                double x1 = (hi - lo)/3 + lo;
                double x2 = (hi - lo)/3*2 + lo;
                double va1 = GetViewAngle(x[i], y[i], x[(t + 1)%n], y[(t + 1)%n], x1, r);
                double va2 = GetViewAngle(x[i], y[i], x[(t + 1)%n], y[(t + 1)%n], x2, r);
                angle = max(va1, va2);
                if (va1 > va2)
                    hi = x2;
                else
                    lo = x1;
            }
            if (angle > bestAngle){
                bestAngle = angle;
                bestX = cos(lo)*r;
                bestY = sin(lo)*r;
            }
            double dif = start[(t + 1) % n] - stop[i];
            if (dif > M_PI)
                dif -= 2. * M_PI;
            if (dif <- M_PI)
                dif += 2. * M_PI;
            if (dif > 0)
                break;
            t = (t + 1)%n;
        }
    }
    printf("%.10f\n", bestAngle);
    return 0;
}
