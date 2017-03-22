#include <stdio.h>
#include <string.h>
typedef struct item
{
	int c;
	int n;
} item;

void quicksort(item* f, int l, int r)
{
	int i = l;
	int j = r;
	item p = f[l];
	while (j > i) {
		while (j > i && f[j].n <= p.n) --j;
		f[i].c = f[j].c;
		f[i].n = f[j].n;
		while (i < j && f[i].n >= p.n) ++i;
		f[j].c = f[i].c;
		f[j].n = f[i].n;
	}
	f[i].c = p.c;
	f[i].n = p.n;

	if (l < i - 1) quicksort(f, l, i - 1);
	if (r > i + 1) quicksort(f, i + 1, r);
}

char* frequencySort(char* s)
{
	if (s == 0) {
		return 0;
	}
	item f[95] = { 0 };
	for (int i = 0; i < 95; ++i) {
		f[i].c = i;
	}

	int len = strlen(s);
	for (int i = 0; i < len; ++i) {
		++(f[s[i] - 32].n);
	}

	quicksort(f, 0, 94);

	char* p = s;
	for (int i = 0; i < 95; ++i) {
		for (int j = 0; j < f[i].n; ++j) {
			*(p++) = (char)(f[i].c + 32);
		}
	}

	return s;
}




