#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef unsigned long DWORD;

#define MAX_COUNT	1000
#define MAX_DIG		16

DWORD sumsqdig(DWORD val, DWORD base)
{
	DWORD dig, result = 0;
	while(val > 0) {
		dig = val % base;
		result += dig*dig;
		val = (val - dig)/base;
	}
	return result;
}

char inbuf[256];

int main()
{
	int nprob, curprob, index, base;
	DWORD init, ret;
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
		if(sscanf(&(inbuf[0]), "%d %d %lu", &index, &base, &init) != 3)
		{
			fprintf(stderr, "scan failed on problem header problem index %d\n",
				curprob);
			return -6;
		}
		if(index != curprob)
		{
			fprintf(stderr, "problem index %d not = expected problem %d\n",
				index, curprob);
			return -7;
		}
		if((base < 3) || (base > 16)) {
			fprintf(stderr, "problem index %d base %d not in range 3 .. 16\n",
				index, base);
			return -9;
		}
		ret = sumsqdig(init, base);
		printf("%d %lu\n", curprob, ret);
	}
	return 0;
}

