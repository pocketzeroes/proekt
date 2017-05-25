/*
test 53 tle
*/
#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#ifndef min
double min(double a, double b) { return a<b ? a : b; }
double max(double a, double b) { return a>b ? a : b; }
#endif

typedef struct TPointS {
	double x, y;
}TPoint;

TPoint newPoint(double x, double y) {
	TPoint rez;
	rez.x = x;
	rez.y = y;
	return rez;
}

TPoint operatorAdd(TPoint a, TPoint b) {
	return newPoint(a.x + b.x, a.y + b.y);
}
TPoint operatorSub(TPoint a, TPoint b) {
	return newPoint(a.x - b.x, a.y - b.y);
}
double operatorMul(TPoint a, TPoint b) {
	return a.x*b.x + a.y*b.y;
}
TPoint operatorTms(TPoint a, double t) {
	return newPoint(t*a.x, t*a.y);
}
double operatorMod(TPoint a, TPoint b) {
	return a.x*b.y - a.y*b.x;
}
double operatorSqr(TPoint a) {
	return sqrt(operatorMul(a, a));
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
TPoint *pushback(TPoint *array, int *size, TPoint value) {
	TPoint *output = resizeArray(array, TPoint, *size + 1);
	output[(*size)++] = value;
	return output;
}
typedef struct vecS {
	TPoint*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz = 0;
	return rez;
}

//////////

TPoint gp;
TPoint gq;
int cmpPt(const void*pa, const void*pb) {
	TPoint*a = (TPoint*)pa;
	TPoint*b = (TPoint*)pb;
	return (operatorMul(operatorSub(gp, *a), operatorSub(*b, *a)) < operatorMul(operatorSub(gq, *a), operatorSub(*b, *a))) ? -1 : 1;
}

enum { maxn = 201 };
#define eps 1e-9
int n;
TPoint p[maxn];

bool inside(TPoint q) {
	for (int i = 0; i<n; i++) {
		if (fabs(operatorMod(operatorSub(q, p[i]), operatorSub(p[i + 1], p[i]))) > eps)
			continue;
		if (operatorMul(operatorSub(q, p[i]), operatorSub(p[i + 1], p[i])) < -eps)
			continue;
		if (operatorMul(operatorSub(q, p[i + 1]), operatorSub(p[i], p[i + 1]))    < -eps)
			continue;
		return true;
	}
	int fl = 0;
	for (int i = 0; i<n; i++) {
		TPoint a = p[i], b = p[i + 1];
		if (fabs(a.x - b.x)<eps)
			continue;
		if (a.x>b.x) {
			TPoint tmp = a; a = b; b = tmp;
		}
		if (q.x<a.x - eps)
			continue;
		if (q.x>b.x - eps)
			continue;
		if (operatorMod(operatorSub(q, a), operatorSub(b, a)) > 0)
			fl ^= 1;
	}
	return fl;
}
void intersect(TPoint p, TPoint q, TPoint a, TPoint b, vec*ints) {
	double na = operatorMod(operatorSub(a, p), operatorSub(q, p)),
		nb = operatorMod(operatorSub(b, p), operatorSub(q, p));
	if (na*nb > eps)
		return;
	if (fabs(na - nb) < eps)
		return;
	ints->ptr = pushback(ints->ptr, &ints->sz, operatorAdd(a, operatorTms(operatorSub(b, a), (na / (na - nb)))));
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
	p[n] = p[0];
	double ans = 0.0;
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<i; j++) {
			TPoint a = p[i], b = p[j];
			vec ints = newVec();
			ints.ptr = pushback(ints.ptr, &ints.sz, operatorAdd(a, operatorTms(operatorSub(b, a), 1e7)));
			ints.ptr = pushback(ints.ptr, &ints.sz, operatorAdd(a, operatorTms(operatorSub(b, a), -1e7)));
			for (int k = 0; k<n; k++) {
				intersect(a, b, p[k], p[k + 1], &ints);
			}
			gp = a;
			gq = b;
			qsort(ints.ptr, ints.sz, sizeof(TPoint), cmpPt);
			TPoint prev;
			bool any = false;
			for (int k = 0; k + 1<ints.sz; k++) {
				TPoint ch = operatorTms(operatorAdd(ints.ptr[k], ints.ptr[k + 1]), 0.5);
				if (!inside(ch))
					prev = ints.ptr[k + 1];
				ans = max(ans, operatorSqr(operatorSub(ints.ptr[k + 1], prev)));
			}
		}
	}
	printf("%.10f\n", ans);
	return 0;
}

























