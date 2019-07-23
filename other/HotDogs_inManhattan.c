#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXW 1000
#define MAXH 1000
#define ABS(a) ((a) < 0 ? -(a) : (a))

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int dist[MAXW][MAXH];
int leftmost[MAXH];
int rightmost[MAXH];
int Q[10*MAXW*MAXH];
int Qstart, Qend;

void push(int i) {
	Q[Qend++] = i;
}

int pop() {
	return Q[Qstart++];
}

bool possible(int d, int h, int w) {
	int x, y, y2;
	for(y = 0; y < h; y++) {
		leftmost[y] = rightmost[y] = -1;
		for(x = 0; x < w; x++) {
			if(dist[x][y] < d) continue;
			if(leftmost[y] == -1) leftmost[y] = x;
			rightmost[y] = x;
		}
		if(leftmost[y] == -1) continue;
		for(y2 = 0; y2 <= y; y2++) {
			if(leftmost[y2] == -1) continue;
			if(ABS(y-y2) + ABS(leftmost[y] - rightmost[y2]) >= d
			|| ABS(y-y2) + ABS(rightmost[y] - leftmost[y2]) >= d) {
				return true;
			}
		}
	}
	return false;
}

void testcase() {
	int n, w, h, i, x, y, d, up, low, end;
	scanf("%d %d %d\n", &n, &w, &h);
	Qstart = Qend = 0;
	for(i=0;i<n;i++) {
		scanf("%d %d\n", &x, &y);
		push(x); push(y);
	}
	
	memset(dist, 127, sizeof(dist));
	d = 0;
	while(Qstart < Qend) {
		end = Qend;
		while(Qstart < end) {
			x = pop(); y = pop();
			if(dist[x][y] <= d) continue;
			dist[x][y] = d;
			for(i = 0; i < 4; i++) {
				if(x+dx[i] < 0 || x+dx[i] >= w) continue;
				if(y+dy[i] < 0 || y+dy[i] >= h) continue;
				if(dist[x+dx[i]][y+dy[i]] <= d) continue;
				push(x+dx[i]); push(y+dy[i]);
			}
		}
		d++;
	}

	low = 1;
	up = w+h;
	while(up != low) {
		d = (up+low+1)/2;
		if(possible(d, h, w))
			low = d;
		else
			up = d - 1;
	}
	printf("%d\n", low);
}


int main() {
	int t;
	scanf("%d\n", &t);
	while(t--) testcase();
	return 0;
}