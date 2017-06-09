#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef struct RandGenS{
	int x, y, z;
}RandGen;

int nextInt(RandGen*rg){
    int t = rg->x ^ (rg->x << 11);
    rg->x = rg->y;
    rg->y = rg->z;
    rg->z ^= (rg->z >> 19) ^ t ^ (t >> 8);
    return rg->z;
}
int random_choice(RandGen*rg, int N){
    return nextInt(rg) % N;
}

#define ran 788888
unsigned long long int a[ran];
int bit[ran];

int lowbit(int x){
    return x&-x;
}
void add(int x,int y){
	while(x < ran){
		bit[x] += y;
		x += lowbit(x);
	}
}
void flipPosition(int poz) {
	unsigned long long int mask = 1llu << (poz&63);
	int pos = poz >> 6;
	if(a[pos]&mask){
		a[pos] -= mask;
		add(pos+1, -1);
	}
    else{
		a[pos] += mask;
		add(pos+1, 1);
	}
}
int query(int x){
	if(x<0)return 0;
	unsigned long long int mask = 1llu << (x&63);
	int pos = x >> 6;
	if(mask>0)mask = mask-1+mask;
	int res = __builtin_popcountll(a[pos]&mask);
	for(int y = pos; y; y-=lowbit(y)){
		res += bit[y];
	}
	return res;
}
int getCount(int st, int fn) {
	return query(fn) - query(st-1);
}
int main() {
	int N, M;
	RandGen rng;
	scanf("%d %d %d %d %d", &N, &M, &rng.x, &rng.y, &rng.z);
	long long hashSol = 0;
	for (long long i = 0; i < M; i++) {
		if (random_choice(&rng, 2) == 0) {
			const int poz = random_choice(&rng, N);
			flipPosition(poz);
		}
		else {
			int st = random_choice(&rng, N), fn = random_choice(&rng, N);
			if (st > fn) {
				SWAP(st, fn);
			}
			hashSol ^= i * getCount(st, fn);
		}
	}
	printf("%lld\n", hashSol);
}






















































