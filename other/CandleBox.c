#include <stdio.h>

enum{ RSTART = 4};
enum{ TSTART = 3};

int main(){
	int d, Rsum, Tsum, Rbox, Tbox, Ra, Ta;
	scanf("%d", &d);
	scanf("%d", &Rbox);
	scanf("%d", &Tbox);
	Rsum = 0;
	Tsum = 0;
	Ra = RSTART;
	Ta = TSTART;
	while(Rsum + Tsum < Rbox + Tbox){
		Rsum += Ra;
		Ra++;
		if(Ra >= TSTART + d){
			Tsum += Ta;
			Ta++;
		}
	}
	printf("%d\n", Rbox-Rsum);
	return 0;
}
