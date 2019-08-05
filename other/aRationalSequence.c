#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT 2147483647
char inbuf[256];


int GetEltIndex(int in_num, int in_denom, int prob_num){
	int val, mask;
	int bit, num, denom;

	mask = 1;
	val = 0;
	bit = 0;
	num = in_num;
	denom = in_denom;
	while((bit < 31) && (num != denom)) {
		if(num > denom) {
			val |= mask;
			num = num - denom;
		} else {
			denom = denom - num;
		}
		mask <<= 1;
		bit++;
	}
	if(bit >= 31) {
		fprintf(stderr, "Over flow on problem %d %d/%d\r\n", prob_num, in_num, in_denom);
		return -11;
	}
	if(num != 1) {
		fprintf(stderr, "num %d denom %d not relatively prime (GCD %d) problem %d\r\n", in_num, in_denom, num, prob_num);
		return -12;
	}
	val |= mask;
	return val;
}
int main(){
	int nprob, curprob, idx, num, denom, ret;

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
			fprintf(stderr, "Read failed on problem %d data\n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%d %d/%d", &idx, &num, &denom) != 3)
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
		if((num < 1) || (num > MAX_INPUT)) {
			fprintf(stderr, "problem index %d numerator %d not in range 1-%d\n",
				curprob, num, MAX_INPUT);
			return -7;
		}
		if((denom < 1) || (denom > MAX_INPUT)) {
			fprintf(stderr, "problem index %d denominator %d not in range 1-%d\n",
				curprob, denom, MAX_INPUT);
			return -7;
		}
		ret = GetEltIndex(num, denom, curprob);
		if(ret <= 0) {
			return ret;
		}
		printf("%d %d\n", curprob, ret);
	}
	return 0;
}
