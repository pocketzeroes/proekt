#include<stdio.h>
#include<stdlib.h>

typedef long long ll;
ll*x, *y;
double sums[1000000];
int f[1000000];
int l[1000000];

double opt(ll*a, int n){
	int ns = 0;
	for (int i = 0; i < n; i++) {
		sums[ns] = a[i];
		f[ns] = i;
		l[ns] = i;
		while (ns > 0 && sums[ns]/(l[ns] - f[ns] + 1) < sums[ns-1]/(l[ns-1] - f[ns-1] + 1))
			sums[ns-1] += sums[ns], l[ns-1] = l[ns], ns--;
		ns++;
	}
	double v = 0;
	for (int i = 0; i < ns; i++)
        for (int j = f[i]; j <= l[i]; j++) {
            double d = sums[i]/(l[i] - f[i] + 1) - a[j];
            v += d*d;
        }
	return v;
}
int main(){
	int n;
    scanf("%d",&n);
	x = (ll*) calloc(n,sizeof(ll));
	y = (ll*) calloc(n,sizeof(ll));
	for (int i = 0; i < n; i++)
        scanf("%lld %lld", x+i, y+i);
	printf("%f\n", opt(x,n) + opt(y,n));
    return 0;
}
