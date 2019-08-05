#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX_NODES	20
#define MAX_QUERIES	10

double Adjacent[MAX_NODES + 1][MAX_NODES + MAX_QUERIES];
int query1[MAX_QUERIES], query2[MAX_QUERIES];

int AdjacentInit(int nnodes, int nqueries)
{
	int i, j;
	for(i = 0; i <= nnodes ; i++) {
		for(j = 0; j < nnodes + nqueries ; j++) {
			Adjacent[i][j] = 0.0;
		}
	}
	for(i = 0; i < nnodes ; i++) {
		Adjacent[nnodes][i] = 1.0;
	}
	return 0;
}

int ScanEdgeData(int nnodes, char *pb)
{
	int val, node, count, i;
	node = count = 0;
	while((*pb != 0) && (isspace(*pb))) pb++;
	if((*pb == 0) || (!isdigit(*pb))){
		return -1;
	}
	while(isdigit(*pb)) {
		node = (node * 10) + (*pb - '0');
		pb++;
	}
	if((*pb == 0) || (!isspace(*pb))) return -2;
	while((*pb != 0) && (isspace(*pb))) pb++;
	if((*pb == 0) || (!isdigit(*pb))) return -3;
	while(isdigit(*pb)) {
		count = (count * 10) + (*pb - '0');
		pb++;
	}
	Adjacent[node-1][node-1] += (double)count;
	for(i = 0; i < count ; i++) {
		if((*pb == 0) || (!isspace(*pb))) return -4;
		while((*pb != 0) && (isspace(*pb))) pb++;
		if((*pb == 0) || (!isdigit(*pb))) return -5;
		val = 0;
		while(isdigit(*pb)) {
			val = (val * 10) + (*pb - '0');
			pb++;
		}
		if((val == 0) || (val > nnodes)) {
			fprintf(stderr, "node %d val %d not in range 1 .. %d \n", i, val, nnodes);
			return -6;
		}
		Adjacent[node-1][val-1] = -1.0;
		Adjacent[val-1][node-1] = -1.0;
		Adjacent[val-1][val-1] += 1.0;
	}
	return count;
}

int FindMaxRow(int nnodes, int nqueries, int currow)
{
	int i, maxrow;
	double max, tmp;
	max = fabs(Adjacent[currow][currow]);
	maxrow = currow;
	for(i = currow + 1; i <= nnodes ; i++) {
		tmp = fabs(Adjacent[i][currow]);
		if(tmp > max) {
			max = tmp;
			maxrow = i;
		}
	}
	return maxrow;
}

void SwapRows(int maxrow, int currow, int nnodes, int nqueries)
{
	int i, ncols;
	double tmp;
	ncols = nnodes + nqueries;
	for(i = 0; i < ncols ; i++) {
		tmp = Adjacent[currow][i];
		Adjacent[currow][i] = Adjacent[maxrow][i];
		Adjacent[maxrow][i] = tmp;
	}
}

int Eliminate(int currow, int nrows, int ncols)
{
	int i, j;
	double factor;
	for(i = 0; i < nrows; i++) {
		if(i == currow) {
			continue;
		}
		factor = Adjacent[i][currow];
		for(j = currow; j < ncols ; j++) {
			Adjacent[i][j] -= factor*Adjacent[currow][j];
		}
	}
	return 0;
}

void DumpMatrix(int nrows, int ncols)
{
	int i, j;
	for(i = 0; i < nrows ; i++){
		for(j = 0; j < ncols ; j++) {
			printf("%.2lf ", Adjacent[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int SolveMatrix(int nnodes, int nqueries)
{
	int nrows, ncols, currow, maxrow, i;
	double pivot;
	ncols = nnodes + nqueries;
	nrows = nnodes + 1;
	for(currow = 0; currow < nnodes; currow++) {
		maxrow = FindMaxRow(nnodes, nqueries, currow);
		if(maxrow != currow) {
			SwapRows(maxrow, currow, nnodes, nqueries);
		}
		pivot = Adjacent[currow][currow];
		if(fabs(pivot) < .001) {
			return -1;
		}
		pivot = 1.0/pivot;
		for(i = currow; i < ncols ; i++) {
			Adjacent[currow][i] *= pivot;
		}
		Eliminate(currow, nrows, ncols);
	}
	return 0;
}

char inbuf[256];
int main()
{
	int nprob=1, curprob=1, index=1, nnodes, nqueries, nedges;
	int i, edgecnt, edgelines, queryno;
	double dist;

	for(curprob = 1; curprob <= nprob ; curprob++)
	{
		if(fgets(&(inbuf[0]), 255, stdin) == NULL)
		{
			fprintf(stderr, "Read failed on problem %d header\n", curprob);
			return -3;
		}
		if(sscanf(&(inbuf[0]), "%d %d %d", &nnodes, &nqueries, &nedges) != 3) {
			fprintf(stderr, "scan failed on problem %d\n", curprob);
			return -4;
		}
		if((nnodes > MAX_NODES) || (nqueries > MAX_QUERIES)) {
			fprintf(stderr, "prob %d: nnodes %d > max %d or nqueries %d > max %d\n",
			curprob, nnodes, MAX_NODES, nqueries, MAX_QUERIES);
			return -6;
		}
		AdjacentInit(nnodes, nqueries);
		edgecnt = edgelines = 0;
		while(edgecnt < nedges) {
			if(fgets(&(inbuf[0]), 255, stdin) == NULL)
			{
				fprintf(stderr, "Read failed on problem %d edgeline %d\n", curprob, edgelines);
				return -7;
			}
			if((i = ScanEdgeData(nnodes, &(inbuf[0]))) < 0) {
				fprintf(stderr, "scan failed on problem %d edgeline %d\n", curprob, edgelines);
				return -8;
			}
			edgelines++;
			edgecnt += i;
		}
		for(i = 0; i < nqueries ; i++) {
			if(fgets(&(inbuf[0]), 255, stdin) == NULL)
			{
				fprintf(stderr, "Read failed on problem %d query %d\n", curprob, i+1);
				return -9;
			}
			if(sscanf(&(inbuf[0]), "%d %d %d", &queryno, &(query1[i]), &(query2[i])) != 3) {
				fprintf(stderr, "scan failed on problem %d query %d\n", curprob, i+1);
				return -10;
			}
			if(i+1 != queryno) {
				fprintf(stderr, "read query num %d != expected %d problem %d\n", queryno, i+1, curprob);
				return -11;
			}
			if((query1[i] < 1) || (query1[i] > nnodes) || (query2[i] < 1) || (query2[i] > nnodes) || (query1[i] == query2[i])) {
				fprintf(stderr, "bad queryid1 %d or queryid2 %d problem %d query %d\n",
					query1, query2, curprob, i+1);
				return -12;
			}
			Adjacent[query1[i]-1][nnodes + i] = 1.0;
			Adjacent[query2[i]-1][nnodes + i] = -1.0;
		}
		if((i = SolveMatrix(nnodes, nqueries)) != 0) {
			fprintf(stderr, "error retrun %d from SolveMatrix problem %d\n", i, curprob);
			return -13;
		} 
    else {
			for(i = 0; i < nqueries ; i++) {
				dist = fabs(Adjacent[query1[i]-1][nnodes + i] - Adjacent[query2[i]-1][nnodes + i]);
				printf("%.6lf\n", dist);
			}
		}
	}
	return 0;
}
