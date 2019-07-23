#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int M, N, a, b, d, mindist;
int oC[123][2], iC[123][2];
int di[123][123];
int oCh[123];

void TrySolution(){
	int dist = 0;
	int i = 0;
	int nr = 0;
	bool first = true;
	while ((i != 0) || (first)) {
		first = false;
		dist += di[i][oC[i][oCh[i]]];
		i = oC[i][oCh[i]];
		nr++;
	}
	if (nr == N) {
		if (dist < mindist) {
			mindist = dist;
		}
	}
  else {
		;
	}
}
void UnChangeChoice(int i, int j){
	oCh[i] = -1;
	int n = oC[i][j]; 
	int ind = (iC[n][0] == i); 
	int m = iC[n][ind]; 
 	if (m == -1)
 		return;
 	int ond = (oC[m][0] == n); 
	if (oCh[m] == -1)
		return;
	UnChangeChoice(m,ond);
	return;	
}
void ChangeChoice(int i, int j) {
	oCh[i] = j;
	int n = oC[i][j];
	int ind = (iC[n][0] == i);
	int m = iC[n][ind];
	if (m == -1)
		return;
	int ond = (oC[m][0] == n);
	if (oCh[m] == ond)
		return;
	ChangeChoice(m,ond);
	return;	
}
void TryAllChoices(int i) {
	if (i == N) {
		TrySolution();
		return;
	}
	if (oCh[i] == -1) {
		ChangeChoice(i,0);
		TryAllChoices(i+1);
		UnChangeChoice(i,0);
		ChangeChoice(i,1);
		TryAllChoices(i+1);
		UnChangeChoice(i,1);
	}
  else {
		TryAllChoices(i+1);
	}
}
void doit(){
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++){
		oC[i][0] = -1;
		iC[i][0] = -1;
		oCh[i] = -1;
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &d);
		if (oC[a][0] == -1) {
			oC[a][0] = b;
			oC[a][1] = -1;
			oCh[a] = 0;
		} 
    else {
			oC[a][1] = b;
			oCh[a] = -1;	
		}
		if (iC[b][0] == -1) {
			iC[b][0] = a;
			iC[b][1] = -1;
		} 
    else
			iC[b][1] = a;
		di[a][b] = d;
	}
	mindist = 123456789;
	TryAllChoices(0);
	printf("%d\n", mindist);
}
int main () {
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		doit();
	return 0;
}
