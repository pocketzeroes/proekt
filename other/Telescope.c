#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

int dx[4] = { 1, 0,-1, 0 };
int dy[4] = { 0, 1, 0,-1 };
enum{ maxval = 0xFFFF};
int N,R,C;
int**pix;
int**orig;
int**sum;
int ncomp;

int**alloc(){
  int**rv=calloc(C, sizeof(int*));
  for(int i=0;i<C;i++)
    rv[i] = calloc(R, sizeof(int));
  return rv;
}
void unblur(){
	if ( N==1 ){
		for(int y=0; y<R; y++)
			for(int x=0; x<C; x++)
				if ( pix[x][y]>0 )
          orig[x][y] = -1;
		return;
	}
	int n = N/2, s = N*N;
	for(int y=n; y<R-n; y++) {
		for(int x=n; x<C-n; x++) {
			int x1 = max(0,x-N);
			int y1 = max(0,y-N);
			sum[x][y] = sum[x-1][y]+sum[x][y-1]-sum[x-1][y-1];
			if ( pix[x-n][y-n]>(sum[x][y]-sum[x1][y]-sum[x][y1]+sum[x1][y1])*maxval/s ) {
				orig[x][y] = -1;
			}
			sum[x][y] += -orig[x][y];
		}
	}
}
void fill(int x, int y, int c){
	if ( orig[x][y]!=-1 )
    return;
	orig[x][y] = c;
	for(int d=0; d<4; d++){
		int x1 = x+dx[d];
		int y1 = y+dy[d];
		if ( 0<=x1 && x1<C && 0<=y1 && y1<R && orig[x1][y1]==-1 )
      fill(x1,y1,c);
	}
}
void floodfill(){
	ncomp = 0;
	for(int y=0; y<R; y++)
		for(int x=0; x<C; x++)
			if(orig[x][y] == -1)
        fill(x, y, ++ncomp);
}
int main(){
	scanf("%d %d %d", &N, &R, &C);
	pix  = alloc();
  orig = alloc();
  sum  = alloc();
	for(int y=0; y<R; y++)
		for(int x=0; x<C; x++)
			scanf("%x", &pix[x][y]);
	unblur();
	floodfill();
	printf("%d\n", ncomp);
	return 0;
}

