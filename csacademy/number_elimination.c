#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>


enum{ kMod  =(int) 1e9+7}; 
enum{ kMaxN =(int) 1e5+5};
int fact[kMaxN], inv_fact[kMaxN];
int num_ways[kMaxN];

int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int mypow(int a, int p) {
	int rez = 1;
	while (p) {
		if (p & 1) {
			rez = (1LL * rez * a) % kMod;
		}
		a = (1LL * a * a) % kMod;
		p >>= 1;
	}
	return rez;
}
void init() {
	fact[0] = 1;
	for (int i = 1; i < kMaxN; i += 1) {
		fact[i] = (1LL * fact[i - 1] * i) % kMod;
	}
	inv_fact[kMaxN - 1] = mypow(fact[kMaxN - 1], kMod - 2);
	inv_fact[0] = 1;
	for (int i = kMaxN - 2; i; i -= 1) {
		inv_fact[i] = (1LL * (i + 1) * inv_fact[i + 1]) % kMod;
	}
	num_ways[1] = 1;
	for (int i = 2; i < kMaxN; i += 1) {
		int current_ways = (1LL * i * (i - 1) / 2) % kMod;
		num_ways[i] = (1LL * num_ways[i - 1] * current_ways) % kMod;
	}
}
int comb(int n, int k) {
	int rez = 1;
	rez = (1LL * rez * fact[n]) % kMod;
	rez = (1LL * rez * inv_fact[k]) % kMod;
	rez = (1LL * rez * inv_fact[n - k]) % kMod;
	return rez;
}
int main() {
	init();
	int n; 
    scanf("%d", &n);
    int elements[n];
	for (int i = 0; i < n; i++){
		int x; 
        scanf("%d", &x);
		elements[i] = x;
	}
	int answer = 1;
	qsort(elements,n,sizeof(int),cmp);
	for (int left = 0; left < n; ) {
		int right = left;
		while (right < n && elements[left] == elements[right]) {
			right += 1;
		}
		int bonus = 0;
		if (left == 0) {
			bonus = 1;
		} else {
			for (int un_matched = 1; un_matched <= right - left; un_matched += 1) {
				int matched = right - left - un_matched;
				bonus = (bonus + 1LL * comb(left + matched - 1, matched) * un_matched) % kMod;
			}
		}
		bonus = (1LL * bonus * num_ways[right - left]) % kMod;
		answer = (1LL * answer * bonus) % kMod;
		left = right;
	}
	printf("%d\n", answer);
	return 0;
}

























































