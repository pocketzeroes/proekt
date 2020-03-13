#include <stdio.h>
#include <string.h>

int buy[1001], sell[1001];

int main() {
	int tc, x, y, b, s;
	char type[100];
	scanf("%d", &tc);
	while(tc--) {
		int n, last_deal = -1;
		scanf("%d", &n);
		memset(buy, 0, sizeof(buy));
		memset(sell, 0, sizeof(sell));
		while(n--) {
			scanf("%s %d shares at %d", type, &x, &y);
			if (type[0] == 'b')
				buy[y] += x;
			else
				sell[y] += x;
			b = 1000;
			while(b > 0 && !buy[b])
				--b;
			for (s=1; s<1001; ++s) {
				while(sell[s] > 0) {
					if (b >= s) {
						last_deal = s;
						if (buy[b] >= sell[s]) {
							buy[b] -= sell[s];
							sell[s] = 0;
						}
						else {
							sell[s] -= buy[b];
							buy[b] = 0;
						}
						while(b > 0 && !buy[b])
							--b;
					}
					else
						break;
				}
				if (sell[s] > 0)
					break;
			}
			if (s == 1001)
				printf("- ");
			else
				printf("%d ", s);
			if (b == 0)
				printf("- ");
			else
				printf("%d ", b);
			if (last_deal == -1)
				puts("-");
			else
				printf("%d\n", last_deal);
		}
	}
	return 0;
}
