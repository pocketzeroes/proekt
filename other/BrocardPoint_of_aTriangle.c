#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define EPS .0001
#define PI (3.141599)

typedef unsigned long DWORD;
#define MAX_ORDER	10000
char inbuf[256];
double A[2], B[2], C[2];
double P[2], P1[2], P2[2];
double AB[2], BC[2], CA[2], AP[2], BP[2], CP[2];

typedef struct _line_
{
	double x0;
	double dx;
	double y0;
	double dy;
} LINE, *PLINE;


int LineInter(PLINE pl1, PLINE pl2, double *pres)
{
	double num, denom, t;
	denom = pl1->dx * pl2->dy - pl1->dy*pl2->dx;
	if(fabs(denom) < EPS) return -3;
	num = (pl2->x0 - pl1->x0)*pl2->dy - (pl2->y0 - pl1->y0)*pl2->dx;
	t = num/denom;
	pres[0] = pl1->x0 + t*pl1->dx;
	pres[1] = pl1->y0 + t*pl1->dy;
	return 0;
}

int MakeUnitVects()
{
	double norm, denom;
	AB[0] = B[0] - A[0];
	AB[1] = B[1] - A[1];
	norm = AB[0]*AB[0] + AB[1]*AB[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	AB[0] *= denom;
	AB[1] *= denom;

	BC[0] = C[0] - B[0];
	BC[1] = C[1] - B[1];
	norm = BC[0]*BC[0] + BC[1]*BC[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	BC[0] *= denom;
	BC[1] *= denom;

	CA[0] = A[0] - C[0];
	CA[1] = A[1] - C[1];
	norm = CA[0]*CA[0] + CA[1]*CA[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	CA[0] *= denom;
	CA[1] *= denom;

	if(fabs(AB[0]*CA[1] - AB[1]*CA[0]) < EPS) return -2;
	if(fabs(BC[0]*AB[1] - BC[1]*AB[0]) < EPS) return -2;
	if(fabs(CA[0]*BC[1] - CA[1]*BC[0]) < EPS) return -2;

	return 0;
}

int BrocardFormula()
{
	double cotA, cotB, cotC, cotP, BrocAng, c, s;
	LINE l1, l2, l3;
	double PAB[2], PBC[2], PCA[2];
	if(MakeUnitVects() != 0) return -1;
	cotA = (AB[0]*CA[0] + AB[1]*CA[1])/(AB[0]*CA[1] - AB[1]*CA[0]);
	cotB = (AB[0]*BC[0] + AB[1]*BC[1])/(BC[0]*AB[1] - BC[1]*AB[0]);
	cotC = (BC[0]*CA[0] + BC[1]*CA[1])/(CA[0]*BC[1] - CA[1]*BC[0]);
	cotP = cotA + cotB + cotC;
	BrocAng = atan2(1.0, cotP);
	c = cos(BrocAng);
	s = sin(BrocAng);
	AP[0] = AB[0]*c - AB[1]*s;
	AP[1] = AB[0]*s + AB[1]*c;
	l1.x0 = A[0]; l1.y0 = A[1]; l1.dx = AP[0]; l1.dy = AP[1];
	BP[0] = BC[0]*c - BC[1]*s;
	BP[1] = BC[0]*s + BC[1]*c;
	l2.x0 = B[0]; l2.y0 = B[1]; l2.dx = BP[0]; l2.dy = BP[1];
	CP[0] = CA[0]*c - CA[1]*s;
	CP[1] = CA[0]*s + CA[1]*c;
	l3.x0 = C[0]; l3.y0 = C[1]; l3.dx = CP[0]; l3.dy = CP[1];

	if(LineInter(&l1, &l2, &PAB[0]) != 0) return -4;
	if(LineInter(&l2, &l3, &PBC[0]) != 0) return -4;
	if(LineInter(&l3, &l1, &PCA[0]) != 0) return -4;
	P[0] = (PAB[0] + PBC[0] + PCA[0])/3.0;
	P[1] = (PAB[1] + PBC[1] + PCA[1])/3.0;
	return 0;
}

int FindSines(double x, double y, double *pSA, double *pSB, double *pSC)
{
	double norm, denom;
	AP[0] = x - A[0];
	AP[1] = y - A[1];
	norm = AP[0]*AP[0] + AP[1]*AP[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	AP[0] *= denom;
	AP[1] *= denom;

	BP[0] = x - B[0];
	BP[1] = y - B[1];
	norm = BP[0]*BP[0] + BP[1]*BP[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	BP[0] *= denom;
	BP[1] *= denom;

	CP[0] = x - C[0];
	CP[1] = y - C[1];
	norm = CP[0]*CP[0] + CP[1]*CP[1];
	if(norm < EPS) return -1;
	denom = 1.0/sqrt(norm);
	CP[0] *= denom;
	CP[1] *= denom;

	*pSA = (AB[0]*AP[1] - AB[1]*AP[0]);
	*pSB = (BC[0]*BP[1] - BC[1]*BP[0]);
	*pSC = (CA[0]*CP[1] - CA[1]*CP[0]);

	return 0;
}

int solve(double a, double b, double c, double d, double y0, double y1, double *pres)
{
	double denom;
	denom = a*d - b*c;
	if(fabs(denom) < EPS) return -1;
	pres[0] = (y0*d - y1*b)/denom;
	pres[1] = (a*y1 - c*y0)/denom;
	return 0;
}

#define REG_FALSI

int BrocardAngleSearch()
{
	double max, min, cur;
	double angA, angB, angC;
	double err, c, s, bcpt[2], Avect[2], norm;
	LINE l1, l2, l3;
	int itcnt = 0;
#ifdef REG_FALSI
	double maxerr, minerr;
	maxerr = minerr = -1.0;
#endif

	angA = atan2(-(AB[0]*CA[1] - AB[1]*CA[0]), -(AB[0]*CA[0] + AB[1]*CA[1]));
	angB = atan2(-(BC[0]*AB[1] - BC[1]*AB[0]), -(AB[0]*BC[0] + AB[1]*BC[1]));
	angC = atan2(-(CA[0]*BC[1] - CA[1]*BC[0]), -(BC[0]*CA[0] + BC[1]*CA[1]));

	max = PI/6.0;
	if(max > angA) max = angA;
	if(max > angB) max = angB;
	if(max > angC) max = angC;
	min = 0.0;
	cur = 0.5*(max + min);
	if(MakeUnitVects() != 0) return -1;
	err = 1.0;
	while((fabs(err) > .0000001) && (itcnt < 40)) {
		itcnt++;
		c = cos(cur);
		s = sin(cur);
		AP[0] = AB[0]*c - AB[1]*s;
		AP[1] = AB[0]*s + AB[1]*c;
		l1.x0 = A[0]; l1.y0 = A[1]; l1.dx = AP[0]; l1.dy = AP[1];
		BP[0] = BC[0]*c - BC[1]*s;
		BP[1] = BC[0]*s + BC[1]*c;
		l2.x0 = B[0]; l2.y0 = B[1]; l2.dx = BP[0]; l2.dy = BP[1];
		CP[0] = CA[0]*c - CA[1]*s;
		CP[1] = CA[0]*s + CA[1]*c;
		l3.x0 = C[0]; l3.y0 = C[1]; l3.dx = CP[0]; l3.dy = CP[1];
		if(LineInter(&l2, &l3, &(bcpt[0])) != 0) return -4;
		Avect[0] = bcpt[0] - A[0];
		Avect[1] = bcpt[1] - A[1];
		norm = Avect[0]*Avect[0] + Avect[1]*Avect[1];
		norm = sqrt(norm);
		if(norm < EPS) return -5;
		Avect[0] /= norm; Avect[1] /= norm;
		err = AP[0]*Avect[1] - AP[1]*Avect[0];
		if(fabs(err) < .0000001) {
			P[0] = bcpt[0];
			P[1] = bcpt[1];
			return 0;
		}
#ifdef REG_FALSI
		if(err > 0) {
			min = cur;
			minerr = err;
		} else {
			max = cur;
			maxerr = -err;
		}
		if((maxerr > 0.0) && (minerr > 0.0)) {
			cur = (minerr*max + maxerr*min)/(maxerr + minerr);
		} else {
			cur = (max + min)*0.5;
		}
#else
		if(err > 0) {
			min = cur;
		} else {
			max = cur;
		}
		cur = (max + min)*0.5;
#endif
	}
	return -6;
}
int main(){
	int nprob, curprob, idx, ret;

	if(fgets(&(inbuf[0]), 255, stdin) == NULL)
	{
		fprintf(stderr, "Read failed on problem count\n");
		return -1;
	}
	if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)
	{
		fprintf(stderr, "Scan failed on problem count\n");
		return -2;
	}
	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d header\n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%d %lf %lf %lf %lf %lf %lf",
			&idx, &(A[0]), &(A[1]), &(B[0]), &(B[1]), &(C[0]), &(C[1])) != 7)
		{
			fprintf(stderr, "scan failed on problem header problem index %d\n",
				curprob);
			return -6;
		}
		if(idx != curprob)
		{
			fprintf(stderr, "problem index %d not = expected problem %d\n",
				idx, curprob);
			return -7;
		}
		if((ret = BrocardFormula()) == 0) {
			printf("%d %.5f %.5f\n", idx, P[0], P[1]);
		} else {
			printf("BrocFormula ret %d\n", ret);
		}
		P1[0] = P[0]; P1[1] = P[1];
		if((ret = BrocardAngleSearch()) == 0) {
			if((fabs(P1[0] - P[0]) > .00001) || (fabs(P1[1] - P[1]) > .00001)){
				printf("ang %d (%.5f, %.5f) != (%.5f, %.5f)\n", idx, P[0], P[1], P1[0], P1[1]);
			}
		} else {
			printf("BrocAngSearch ret %d\n", ret);
		}
	}
	return 0;
}
