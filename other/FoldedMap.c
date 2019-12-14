#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXMAP  = 1000};
enum{ MAXTILE = 100 };
enum{ MAXSUM  = (MAXMAP+MAXTILE)};

bool data   [MAXMAP][MAXMAP];
int cnt_left[MAXSUM][MAXSUM];
int cnt_tile[MAXSUM][MAXSUM];
int mw, mh, tw, th;

int count_needed(int r, int c){
	int result = 0;
	for(int i=r; i<mh+th; i+=th){
		for(int j=c; j<mw+tw; j+=tw){
			if(cnt_tile[i][j] > 0)
				result++;
		}
	}
	return result;
}
int main(){
	while(1){
		mh=mw=th=tw=0;
		scanf(" %d %d %d %d ", &mh, &mw, &th, &tw);
		if(mh == 0)
			break;
		for(int i=0; i<mh; i++){
			for(int j=0; j<mw; j++){
				char tmpc = fgetc(stdin);
				data[i][j] = (tmpc=='X');
			}
			scanf(" ");
		}
		for(int i=0; i<mh+th; i++){
			int cur_cnt = 0;
			for(int j=0; j<mw+tw; j++){
				if(i<mh && j<mw && data[i][j])
					cur_cnt++;
				if(i<mh && j-tw >= 0 && data[i][j-tw])
					cur_cnt--;
				cnt_left[i][j] = cur_cnt;
			}
		}
		for(int j=0; j<mw+tw; j++){
			int cur_cnt = 0;
			for(int i=0; i<mh+th; i++){
				cur_cnt += cnt_left[i][j];
				if(i-th >= 0)
					cur_cnt -= cnt_left[i-th][j];
				cnt_tile[i][j] = cur_cnt;
			}
		}
		int result = MAXSUM*MAXSUM;
		for(int i=0; i<th; i++){
			for(int j=0; j<tw; j++){
				result = fmin(result, count_needed(i,j));
			}
		}
		printf("%d\n", result);
	}
	return 0;
}
