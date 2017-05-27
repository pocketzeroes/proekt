#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*a,int sz,int v){
  for(int i=0;i<sz;i++)a[i]=v;
}

int**answers;
int**suggestions;
int *who;
int *kind;
int *unknownByKind;
int *fiveByKind;
bool*canBe;
int*remaining;
int answers_length;
int sizes[111100];
void rec(int);
void findOne(int, int);
char buff[64];

int main() {
	int n;
	scanf("%d", &n);
	who   = calloc(21, sizeof(int));
	kind  = calloc(21, sizeof(int));
  fill(kind, 21, 2);
  for(int i=0;i<6 ;i++)kind[i]=0;
  for(int i=6;i<12;i++)kind[i]=1;
	unknownByKind = calloc(3, sizeof(int));
  for(int i=0;i<21;i++){int x=kind[i];++unknownByKind[x];}
	fiveByKind = calloc(3, sizeof(int));
	canBe = calloc(21, sizeof(bool));
	for (int i = 0; i<5; i++) {
    scanf("%s", &buff); int a=buff[0] - 'A';
		who[a] = 1;
    --unknownByKind[kind[a]];
  }
	answers     = calloc(n, sizeof(int*)); for (int i = 0; i<n; i++)answers    [i] = calloc(3, sizeof(int));
	suggestions = calloc(n, sizeof(int*)); for (int i = 0; i<n; i++)suggestions[i] = calloc(3, sizeof(int));

	for (int step = 0; step<n; step++){
		for (int i = 0; i<3; i++){
			scanf("%s", &buff);	suggestions[step][i] = buff[0] - 'A';
		}
		int cur[3];
		int len = 0;
		for (int i = 0; i<3; i++){
			scanf("%s", &buff); char a = buff[0];
			++len;
			if (a == '-') {
				cur[i] = -1;
				continue;
			}
			if (a == '*') {
				cur[i] = -2;
			}
			else {
				cur[i] = a - 'A';
			}
			break;
		}
		for (int i = 0; i < len; i++)answers[step][i] = cur[i];
		sizes[step] = len;
		answers_length = n;
	}
	remaining = calloc(6, sizeof(int));
	remaining[0] = 0;
	remaining[1] = 0;
	remaining[2] = 5;
	remaining[3] = 4;
	remaining[4] = 4;
	remaining[5] = 3;
	rec(0);
	findOne(0, 6);
	findOne(6, 12);
	findOne(12, 21);
}
void findOne(int left, int right) {
	int r = -1;
	for (int i = left; i<right; i++) {
		if (canBe[i]) {
			if (r == -1)
				r = i;
			else {
				r = -2;
			}
		}
	}
	if (r == -1) assert(!"throw new RuntimeException");
	putchar(r == -2 ? '?' : (char)('A' + r));
}
void rec(int p) {
	if (p >= answers_length) {
		for (int i = 0; i<21; i++)if (who[i] == 5 || (who[i] == 0 && fiveByKind[kind[i]]==0)) {
			canBe[i] = true;
		}
		return;
	}
	for (int i = 0; i<3; i++) {
		int x = suggestions[p][i];
		if (who[x] == 0) {
			for (int u = 2; u <= 5; u++)if (remaining[u]>0) {
				who[x] = u;
        --unknownByKind[kind[x]];
  			--remaining[u];
        if(u==5)++fiveByKind[kind[x]];
        if(fiveByKind[kind[x]]==1||(fiveByKind[kind[x]]==0&&unknownByKind[kind[x]]>0))
  				rec(p);
        
				who[x] = 0;
				++remaining[u];
        ++unknownByKind[kind[x]];
        if(u==5)--fiveByKind[kind[x]];
      }
			return;
		}
	}
	for (int i = 0; i<sizes[p]; i++) {
		int w = (p + i + 1) % 4 + 1;
		int a = answers[p][i];
		if (a == -1) {
			for (int z = 0; z<3; z++) {	int x = suggestions[p][z]; if (who[x] == w)	return;}
		}
		else if (a == -2) {
			bool any = false;
			for (int z = 0; z<3; z++) {int x = suggestions[p][z];if (who[x] == w) { any = true; break; };}
			if (!any)return;
		}
		else {
			if (who[a] != w)return;
		}
	}
	rec(p + 1);
}
















































