#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t digsum(int64_t n) {
	int64_t ret = 0;
	while(n>0) {
		ret += n%10;
		n /= 10;
	}
	return ret;
}

int64_t sum(int64_t n) {
	int64_t ret = 0;
	int64_t d = 0;
	int64_t t = 1;
	while(n>0) {
		while(n%10) {
			ret += d * t * 45 / 10;
			ret += digsum(n);
			ret += (digsum(n)-1)*(t-1);
			n--;
		}
		n/=10;
		d++;
		t*=10;
	}
	return ret;
}

void testcase() {
	int64_t a, b;
	scanf("%lld %lld\n", &a, &b);
	printf("%lld\n", sum(b) - sum(a-1));
}

int main() {
	int t;
	scanf("%d\n", &t);
	while(t--) testcase();
	return 0;
}
