#include <stdio.h>
#define DEBUG(x...) {}
#define MAXSAMP  100
#define MAXTIME  (24*60)
int samp;
int pos  [MAXSAMP][MAXTIME];
int tmin [MAXSAMP], 
    tmax [MAXSAMP];
int fprev[MAXSAMP][MAXTIME], 
    fnext[MAXSAMP][MAXTIME];
int queue[MAXSAMP*MAXTIME], qb, qe;
char dig[4][7];
int posdig[4][11];
char digshape[11][8] = {
	"-||.||-",
	"..|..|.",
	"-.|-|.-",
	"-.|-.|-",
	".||-.|.",
	"-|.-.|-",
	"-|.-||-",
	"-.|..|.",
	"-||-||-",
	"-||-.|-",
	"......."
};
char scanstr[10];
char scan_char(){
	scanf("%s", scanstr);
	return scanstr[0];
}
void scan_line1(int pos){
	int i;
	for (i = 0; i < 4; ++i)
		dig[i][pos] = scan_char();
}
void scan_line2(int pos1, int pos2){
	int i;
	for (i = 0; i < 4; ++i){
		dig[i][pos1] = scan_char();
		dig[i][pos2] = scan_char();
	}
}
void scan_time(){
	int d, x, p;
	scan_line1(0);
	scan_line2(1,2);
	scan_line1(3);
	scan_line2(4,5);
	scan_line1(6);
	for (d = 0; d < 4; ++d)
		for (x = 0; x < 11; ++x){
			for (p = 0; p < 7; ++p){
				if (dig[d][p] != '?' && dig[d][p] != digshape[x][p])
                    break;
			}
			posdig[d][x] = (p == 7);
			DEBUG("dig%d[%d]: %d\n", x, d, posdig[d][x]);
		}
}
void form_time(int t, int d[]){
	int h = t/60, m = t%60;
	d[0] = h/10; d[1] = h%10;
	d[2] = m/10; d[3] = m%10;
	if (d[0] == 0) d[0] = 10;
}
void invalidate_pos(int s, int t){
	if (!pos[s][t]) 
        return;
	pos[s][t] = 0;
	queue[qe++] = s*MAXTIME + t;
}
void sample_validate(int s){
	int t, d[4], i;
	for (t = 0; t < MAXTIME; ++t){
		form_time(t, d);
		for (i = 0; i < 4; ++i)
			if (!posdig[i][d[i]]) 
                break;
		pos[s][t] = 1;
		if (i < 4) {
			invalidate_pos(s,t);
		}
	}
}
void invalidate_all(){
	int i, s, t;
	while (qb < qe){
		s = queue[qb] / MAXTIME;
		t = queue[qb++] % MAXTIME;
		if (s > 0)
			for (i = tmin[s]; i <= tmax[s]; ++i){
				int tt = t - i;
				if (tt < 0)
                    tt += MAXTIME;
				if (!--fnext[s-1][tt])
					invalidate_pos(s-1,tt);
			}
		if (s < samp-1)
			for (i = tmin[s+1]; i <= tmax[s+1]; ++i){
				int tt = t + i;
				if (tt >= MAXTIME)
                    tt -= MAXTIME;
				if (!--fprev[s+1][tt])
					invalidate_pos(s+1,tt);
			}
	}
}
void print_output(){
	int s, t, tt, cnt, d[4];
	for (s = 0; s < samp; ++s){
		cnt = 0;
		for (t = 0; t < MAXTIME; ++t){
			if (pos[s][t]){
                tt = t;
                ++cnt;
            }
		}
		if (cnt == 1) {
			form_time(tt, d);
			if (d[0] > 0 && d[0] < 10)
                printf("%d", d[0]);
			printf("%d:%d%d\n", d[1], d[2], d[3]);
		}
        else {
			printf("ambiguous, %d possibilities\n", cnt);
		}
	}
}
int main(){
	for (;;) {
		int s, i;
		scanf("%d", &samp);
		if (samp == 0) 
            break;
		qb = qe = 0;
		for (s = 0; s < samp; ++s) {
			if (s > 0) {
				int dif;
				scanf("%d%d", tmin+s, tmax+s);
				dif = tmax[s] - tmin[s] + 1;
				for (i = 0; i < MAXTIME; ++i) {
					fnext[s-1][i] = fprev[s][i] = dif;
				}
			}
			scan_time();
			sample_validate(s);
		}
		invalidate_all();
		print_output();
		printf("\n");
	}
	return 0;
}
