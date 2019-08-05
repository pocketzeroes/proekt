#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define EPS .00001

double ax, ay, bx, by, cx, cy;
double ccenx, cceny, crad;
double aidirx, aidiry, bidirx, bidiry, cidirx, cidiry;
double px, py, nx, ny, mx, my;
double pnperpx, pnperpy, nmperpx, nmperpy, mpperpx, mpperpy;
double ex, ey, fx, fy, gx, gy, hx, hy, jx, jy, kx, ky;
double efdist, fgdist, ghdist, hjdist, jkdist, kedist;


int find_circum_circle()
{
	double t;
	if(fabs(cy) < EPS) return -1;
	t = 0.5*(cx - bx)/cy;
	ccenx = 0.5*bx;
	cceny = 0.5*cy + t*cx;
	crad = sqrt(ccenx*ccenx + cceny*cceny);
	return 0;
}

int find_pnm()
{
	double d, d1, t, tx, ty, ux, uy;
	d = sqrt(cx*cx + cy*cy);
	tx = cx; ty = cy; ux = d; uy = 0;
	aidirx = 0.5*(tx + ux); aidiry = 0.5*(ty + uy);
	d = sqrt(aidirx*aidirx + aidiry*aidiry);
	aidirx /= d;
	aidiry /= d;
	t = 2.0*(aidirx*(ccenx) + aidiry*(cceny));
	mx = t*aidirx; my = t*aidiry;
	d = sqrt((cx - bx)*(cx - bx) + cy*cy);
	tx = cx; ty = cy; ux = bx - d; uy = 0;
	bidirx = 0.5*(tx + ux) - bx; bidiry = 0.5*(ty + uy) - by;
	d = sqrt(bidirx*bidirx + bidiry*bidiry);
	bidirx /= d;
	bidiry /= d;
	t = 2.0*(bidirx*(ccenx - bx) + bidiry*(cceny));
	nx = t*bidirx + bx; ny = t*bidiry;
	d = sqrt((cx - bx)*(cx - bx) + cy*cy);
	d1 = sqrt(cx*cx + cy*cy);
	tx = bx; ty = by; ux = cx*(1.0 - d/d1); uy = cy*(1.0 - d/d1);
	cidirx = 0.5*(tx + ux) - cx; cidiry = 0.5*(ty + uy) - cy;
	d = sqrt(cidirx*cidirx + cidiry*cidiry);
	cidirx /= d;
	cidiry /= d;
	t = 2.0*(cidirx*(ccenx - cx) + cidiry*(cceny - cy));
	px = t*cidirx + cx; py = t*cidiry + cy;
	return 0;
}

int find_efghjk()
{
	double t, num, denom, diracx, diracy, dirabx, diraby, dirbcx, dirbcy;
	diracx = cx; diracy = cy;
	dirabx = bx; diraby = 0;
	dirbcx = cx - bx; dirbcy = cy;
	pnperpx = (py - ny); pnperpy = (nx - px);
	denom = pnperpx*dirabx + pnperpy*diraby;
	num = pnperpx*(px - 0) + pnperpy*(py - 0);
	t = num/denom;
	ex = 0 + t*dirabx;
	ey = 0 + t*diraby;
	denom = pnperpx*diracx + pnperpy*diracy;
	num = pnperpx*(px - 0) + pnperpy*(py - 0);
	t = num/denom;
	fx = 0 + t*diracx;
	fy = 0 + t*diracy;
	nmperpx = (ny - my); nmperpy = (mx - nx);
	denom = nmperpx*diracx + nmperpy*diracy;
	num = nmperpx*(nx - 0) + nmperpy*(ny - 0);
	t = num/denom;
	gx = 0 + t*diracx;
	gy = 0 + t*diracy;
	denom = nmperpx*dirbcx + nmperpy*dirbcy;
	num = nmperpx*(nx - bx) + nmperpy*(ny - by);
	t = num/denom;
	hx = bx + t*dirbcx;
	hy = 0 + t*dirbcy;
	mpperpx = (py - my); mpperpy = (mx - px);
	denom = mpperpx*dirbcx + mpperpy*dirbcy;
	num = mpperpx*(mx - bx) + mpperpy*(my - 0);
	t = num/denom;
	jx = bx + t*dirbcx;
	jy = 0 + t*dirbcy;
	denom = mpperpx*dirabx + mpperpy*diraby;
	num = mpperpx*(px - 0) + mpperpy*(py - 0);
	t = num/denom;
	kx = 0 + t*dirabx;
	ky = 0 + t*diraby;
	return 0;
}
int find_dists()
{
	efdist = sqrt((ex-fx)*(ex-fx) + (ey-fy)*(ey-fy));
	fgdist = sqrt((gx-fx)*(gx-fx) + (gy-fy)*(gy-fy));
	ghdist = sqrt((hx-gx)*(hx-gx) + (hy-gy)*(hy-gy)); 
	hjdist = sqrt((hx-jx)*(hx-jx) + (hy-jy)*(hy-jy));
	jkdist = sqrt((kx-jx)*(kx-jx) + (ky-jy)*(ky-jy)); 
	kedist = sqrt((ex-kx)*(ex-kx) + (ey-ky)*(ey-ky));
	return 0;
}

char inbuf[256];

int main()
{
	int nprob=1, curprob=1, index=1;
	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d header\n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%lf %lf %lf", &bx, &cx, &cy) != 3)
		{
			fprintf(stderr, "scan failed on problem header problem index %d\n",
				curprob);
			return -6;
		}
		ax = ay = by = 0.0;
		if(find_circum_circle() != 0) {
			fprintf(stderr, "problem index %d not not a triangle\n",
				index);
			return -8;
		}
		find_pnm();
		find_efghjk();
		find_dists();
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", efdist, fgdist, ghdist, hjdist, jkdist, kedist);
	}
	return 0;
}

