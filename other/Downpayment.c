#include <stdio.h>
#include <math.h>

//#define DEBUG
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf 1 ? 0 : 
#endif

double C[20][20];
int l[20];
double r[1000*12][20];
int N, m, t;
double x, y;

struct 
{
  double lefttopay;
  int fromterm, fromtime;
} dp[1000*12+2][20][60];

int chain[1000*12];

main()
{
  int n, i, j, time;
  double minend;
  int minendterm, minendtime;

  scanf("%d", &N);
  dprintf("%d\n", N);
  for (n = 1; n <= N; n++) {
	scanf("%d %lf %lf", &m, &x, &y);
	for (i = 0; i < m; i++)
	  scanf("%d", &(l[i]));
	for (i = 0; i < m; i++)
	  for (j = 0; j < m; j++)
		scanf("%lf", &(C[i][j]));
	scanf("%d", &t);
	for (i = 0; i < t; i++)
	  for (j = 0; j < m; j++)
		scanf("%lf", &(r[i][j]));
	for (i = 0; i < m; i++) {
	  for (j = 0; j < l[i]-1; j++)
		dp[0][i][j].lefttopay = -1;
	  dp[0][i][l[i]-1].lefttopay = x;
	}
	for (time = 1, minend = y+1; minend > y; time++) {
	  dprintf("%d %d\n", time, m);

	  for (i = 0; i < m; i++) {
		for (j = 0; j < 60; j++)
		  dp[time][i][j].lefttopay = -1;
	  }

	  for (i = 0; i < m; i++) {
		/* Do changes in terms */
		for (j = 0; j < m; j++)
		  if (dp[time-1][i][0].lefttopay >= 0) {
			double newdebt = floor(100 * (dp[time-1][i][0].lefttopay * (1 + r[time-1][i] / 100.0) + C[i][j])) / 100;
			dprintf("TIME: %d %d %d %f %f %f %f\n", time, i, j, newdebt, dp[time-1][i][0].lefttopay, x, y);
			if (newdebt <= y) {  /* Loan can be fully paid */
			  if (newdebt < minend) {
				minendterm = i;
				minendtime = 0;
				minend = newdebt;
			  }
			} else {
			  newdebt -= y;
			  dprintf("DP %d %d %d %f\n", time, j, l[j]-1, dp[time][j][l[j]-1].lefttopay);
			  if (dp[time][j][l[j]-1].lefttopay == -1 || newdebt < dp[time][j][l[j]-1].lefttopay) {
				dp[time][j][l[j]-1].lefttopay = newdebt;
				dp[time][j][l[j]-1].fromterm = i;
				dp[time][j][l[j]-1].fromtime = 0;
			  }
			}
		  }
		/* Do no changes in terms */
		for (j = 1; j < l[i]; j++) 
		  if (dp[time-1][i][j].lefttopay >= 0) {
			double newdebt = floor(100 * (dp[time-1][i][j].lefttopay * (1 + r[time-1][i] / 100.0))) / 100;
  		    dprintf("DP2 %d %d %d %f %f\n", time, i, j, dp[time-1][i][j].lefttopay, newdebt);
			if (newdebt <= y) {
			  if (newdebt < minend) {
				minendterm = i;
				minendtime = j;
				minend = newdebt;
			  }
			} else {
			  newdebt -= y;
			  if (dp[time][i][j-1].lefttopay == -1 || newdebt < dp[time][i][j-1].lefttopay) {
				dp[time][i][j-1].lefttopay = newdebt;
				dp[time][i][j-1].fromterm = i;
				dp[time][i][j-1].fromtime = j;
			  }
			}
		  }
	  }
	}
	/* Now the structure dp holds information which backtracks to the start */
	/* Start at minendterm, minendtime, and follow the chain */

#ifdef DEBUG
	{
	  int k;
	  printf("(%d,%d,%d,%lf)\n", minendterm, minendtime, time, minend);
	  for (k = 0; k < t; k++) 
		for (i = 0; i < m; i++)
		  for (j = 0; j < l[i]; j++) {
			printf("t=%d, i=%d, j=%d, lp=%f, f=(%d,%d)\n", k, i, j, dp[k][i][j].lefttopay,
			  dp[k][i][j].fromterm, dp[k][i][j].fromtime);
		  }
	}
#endif

	time -= 2;
	chain[t = time] = minendterm;
	while (time > 0) {
	  dprintf("(%d, %d, %d)\n", time, minendterm, minendtime);
	  chain[time-1] = i = dp[time][minendterm][minendtime].fromterm;
	  j = dp[time][minendterm][minendtime].fromtime;
	  minendterm = i;
	  minendtime = j;
	  time--;
	}
	printf("Test case %d\n", n);
	for (i = 0; i <= t; i++) 
	  printf("Month %d: Alternative %d\n", i+1, chain[i]+1);
	printf("Total: %.2f\n", t*y + minend);
  }
}