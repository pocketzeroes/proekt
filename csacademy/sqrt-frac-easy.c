#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define DBL_EPSILON 2.22044604925031308085e-16
#define EPS DBL_EPSILON

#define FORCE_EVAL(x) do {                        \
	if (sizeof(x) == sizeof(float)) {         \
		volatile float __x;               \
		__x = (x);                        \
	} else if (sizeof(x) == sizeof(double)) { \
		volatile double __x;              \
		__x = (x);                        \
	} else {                                  \
		volatile long double __x;         \
		__x = (x);                        \
	}                                         \
} while(0)

static const double toint = 1/EPS;

double ceil(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	double y;
	if (e >= 0x3ff+52 || x == 0)
		return x;
	if (u.i >> 63)
		y = x - toint + toint - x;
	else
		y = x + toint - toint - x;
	if (e <= 0x3ff-1) {
		FORCE_EVAL(y);
		return u.i >> 63 ? -0.0 : 1;
	}
	if (y < 0)
		return x + y + 1;
	return x + y;
}


double floor(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	double y;
	if (e >= 0x3ff+52 || x == 0)
		return x;
	if (u.i >> 63)
		y = x - toint + toint - x;
	else
		y = x + toint - toint - x;
	if (e <= 0x3ff-1) {
		FORCE_EVAL(y);
		return u.i >> 63 ? -1 : 0;
	}
	if (y > 0)
		return x + y - 1;
	return x + y;
}

typedef long long ll;
const double gEPS = 1e-9;

int main(){
    int t;
    scanf("%d", &t);
    while(t--) {
        ll aux;
        scanf("%lld", &aux);
        double f = (aux / (double) 1e9);
        ll ans = 1;
        for(int i = 1; ; i++) {
            ll s = ceil((i + f) * (i + f));
            ll k = floor((i + f + gEPS) * (i + f + gEPS));
            if(s <= k) {
                ans = s;
                break;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

