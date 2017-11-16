#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAXN 100000
#define INF 1000000000000000000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define SWAP(a,b) { typeof(a) tmp; tmp = a; a = b; b = tmp; }

typedef long long ll;

int n;
ll x[MAXN], y[MAXN];
ll pts[MAXN*2];
ll minx, maxx, miny, maxy;
ll ans;

int medianOfMedians(ll *nums, int left, int right);




ll xline(ll x, ll y) {
	return x - y;
}
ll yline(ll x, ll y) {
	return x + y;
}
ll getx(ll xline, ll yline, bool up) {
	return (xline + yline + (up ? 1 : 0)) / 2;
}
ll gety(ll xline, ll yline, bool up) {
	return yline - getx(xline, yline, !up);
}
ll median_small(ll *nums, int left, int right) {
	int i, j, n;
	n = right - left + 1;
	for(i = left; i <= left + n / 2; i++)
		for(j = i + 1; j <= right; j++)
			if(nums[j] < nums[i])
				SWAP(nums[i], nums[j]);
	return left + n / 2;
}
int partition(ll *nums, int left, int right, int pivotIdx) {
	int i, st;
	ll pivotVal;
	pivotVal = nums[pivotIdx];
	SWAP(nums[pivotIdx], nums[right]);
	st = left;
	for(i = left; i < right; i++) {
		if(nums[i] < pivotVal) {
			SWAP(nums[st], nums[i]);
			st++;
		}
	}
	SWAP(nums[right], nums[st]);
	return st;
}
int selectIdx(ll *nums, int left, int right, int k) {
	int pivotIdx;
	if(left == right) return k;
	pivotIdx = medianOfMedians(nums, left, right);
	pivotIdx = partition(nums, left, right, pivotIdx);
	if(pivotIdx == left || k == pivotIdx)
		return k;
	else if(k < pivotIdx)
		return selectIdx(nums, left, pivotIdx - 1, k);
	else
		return selectIdx(nums, pivotIdx + 1, right, k);
}
int medianOfMedians(ll *nums, int left, int right) {
	int numMedians, i, medianIdx, subLeft, subRight;
	numMedians = ((right - left) + 4) / 5;
	for(i = 0; i < numMedians; i++) {
		subLeft = left + i * 5;
		subRight = subLeft + 4;
		if(subRight > right) subRight = right;
		medianIdx = median_small(nums, subLeft, subRight);
		SWAP(nums[left+i], nums[medianIdx]);
	}
	return selectIdx(nums, left, left + numMedians - 1, left + numMedians / 2);
}
ll median(ll *nums, int n) {
	int idx = selectIdx(nums, 0, n - 1, n / 2);
	return nums[idx];
}
void check(ll xt, ll yt) {
	int i;
	if(!(minx <= xline(xt,yt) && xline(xt,yt) <= maxx && miny <= yline(xt,yt) && yline(xt,yt) <= maxy)) 
    return;
	ll curans = 0;
	for(i = 0; i < n; i++)
		curans += ABS(x[i] - xt) + ABS(y[i] - yt);
	if(curans < ans)
		ans = curans;
}
int main() {
	int i, j;
	ll d, xm, ym;
	scanf("%d\n", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld\n", &x[i], &y[i]);
	scanf("%lld\n", &d);
	minx = miny = -INF;
	maxx = maxy =  INF;
	for(i = 0; i < n; i++) {
		minx = MAX(minx, xline(x[i] - d, y[i]));
		maxx = MIN(maxx, xline(x[i] + d, y[i]));
		miny = MAX(miny, yline(x[i], y[i] - d));
		maxy = MIN(maxy, yline(x[i], y[i] + d));
	}
	if(minx > maxx || miny > maxy) {
		printf("impossible\n");
		return 0;
	}
	ans = INF;
	xm = median(x, n);
	ym = median(y, n);
	check(xm,ym);
	check(getx(minx,miny,true ),gety(minx,miny,true ));
	check(getx(minx,miny,true ),gety(minx,miny,false));
	check(getx(minx,maxy,false),gety(minx,maxy,false));
	check(getx(minx,maxy,true ),gety(minx,maxy,false));
	check(getx(maxx,maxy,false),gety(maxx,maxy,true ));
	check(getx(maxx,maxy,false),gety(maxx,maxy,false));
	check(getx(maxx,miny,true ),gety(maxx,miny,true ));
	check(getx(maxx,miny,false),gety(maxx,miny,true ));
	int border[4][3] = {
		{minx, 1, -minx}, 
		{maxx, 1, -maxx}, 
		{miny, -1, miny}, 
		{maxy, -1, maxy}  
	};
	for(i = 0; i < 4; i++) {
		for(j = 0; j < n; j++) {
			pts[j*2] = x[j];
			pts[j*2+1] = border[i][0] + border[i][1] * y[j];
		}
		xm = median(pts, n * 2);
		ym = border[i][1] * xm + border[i][2];
		check(xm,ym);
	}
	printf("%lld\n", ans);
	return 0;
}


























































