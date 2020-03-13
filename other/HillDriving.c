#include <stdio.h>
#include <math.h>
#include <assert.h>

#define debug(...) fprintf(stderr,__VA_ARGS__)

#define maxr 10010

int r;
double l[maxr], s[maxr];
double a, b, f, vmax;

int reachable(double v, double *t)
{
	int i;
	double vreal, df, fuel = f;
	*t = 0;
	for(i=0; i<r; i++) {
		df = (a*v + b*s[i])*l[i];
		vreal = v;
		if ( df<0 ) {
			df = 0;
			vreal = -b*s[i]/a;
			if ( vreal > vmax ) vreal = vmax;
		}
		if ( fuel<df ) return 0;
		fuel -= df;
		*t += l[i] / vreal;
	}
	return 1;
}

int main()
{
	int run, nruns;
	int i;
	double x, y, t;

	scanf("%d\n",&nruns);

	for(run=1; run<=nruns; run++) {

		scanf("%lf %lf %lf %lf\n%d\n",&a,&b,&vmax,&f,&r);
		if ( a<0.1 || a>100 ||
		     b<0.1 || b>100 ||
		     vmax<10 || vmax>200 ||
		     f<0 || f>50 ) {
			printf("invalid parameters\n");
			return 1;
		}

		for(i=0; i<r; i++) {
			scanf("%lf %lf\n",&x,&y);
			if ( x<1     || x>1000 ||
			     y<-1000 || y>1000 ) {
				printf("invalid distance\n");
				return 1;
			}
			x /= 1000;
			y /= 1000;
			l[i] = sqrt(x*x + y*y);
			s[i] = y / x;
		}

		if ( !reachable(0.0,&t) ) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		double vlo = 1E-6, vhi = vmax, vmid;
		while ( vhi - vlo > 1E-13 ) {
			vmid = (vlo + vhi) / 2;
			if ( reachable(vmid,&t) ) {
				vlo = vmid;
			} else {
				vhi = vmid;
			}
		}
		assert(vlo > 1E-5);

		reachable(vlo,&t);
		if ( t>=24 ) {
			printf("invalid answer %lf >= 24\n",t);
			return 1;
		}
		printf("%.12lg\n",t);
	}

	return 0;
}
