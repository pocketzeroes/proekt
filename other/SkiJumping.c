#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define ABS(x) ((x) > 0 ? (x) : (-(x)))
double g = 9.81;

int main(){
    int numCases;
    scanf("%d", &numCases);
    while (numCases-- > 0) {
        int j, p, H, L;
        scanf("%d %d %d %d", &j, &p, &H, &L);
        double v0 = sqrt(2*g*j);
        int cnt = 0;
        double left = 0.0;
        double right = 1e6;
        while (cnt < 100 && ABS(left - right) > 1e-8){
            cnt++;
            double mid = (left + right) / 2;
            double f = -g/2. * mid*mid / (v0*v0);
            f += H + p;
            double h = H;
            if (mid > 0 && mid < L/2) {
                h = H * (1 - 2 * mid*mid / (L*L));
            }
            else if (L/2 <= mid && mid < L) {
                h = 2*H * (mid/L - 1)*(mid/L - 1);
            }
            else {
                h = 0;
            }
            if (f - h > 0) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        double mid = (left + right) / 2;
        double f = -g/2. * mid*mid / (v0*v0);
        f += H + p;
        double v1 = sqrt(2*g*(j+p+(H-f)));
        double fl = -g * mid / (v0*v0);
        double hl = 0;
        if (mid > 0 && mid < L/2) {
            hl = -4.*H * mid * (1./(L*L));
        }
        else if (L/2 <= mid && mid < L) {
            hl = 2.*H * (2.*mid/(L*L) - 2./L);
        }
        else {
            hl = 0;
        }
        double a = ABS(atan(fl) - atan(hl));
        double pi = 2.*acos(0);
        a = 180. * a / pi;
        printf("%12.12lf %12.12lf %12.12lf\n", mid, v1, a);
    }
    return 0;
}
