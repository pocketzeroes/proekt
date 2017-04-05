#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
typedef struct pair {
	int first;
	int second;
}pair;
pair newPair(int a, int b) {
	pair rez;
	rez.first = a;
	rez.second = b;
	return rez;
}

typedef long long int64;

int main() {
    int n;
    scanf("%d", &n);
    int element[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &element[i]);
    pair neighbours[n + 1];
    int64 result = 0;
    for (int i = 0; i < n; i++) {
        bool valid[n + 1];
        memset(valid,0,sizeof(valid));
        for (int j = i; j < n; j++) 
            valid[element[j]] = true;
        valid[n + 1] = true;
        int last = 0;
        int bigger = (n - i), lower = 0, mid = 0;
        for (int j = 1; j <= n; j++) {
            if(!valid[j]) 
                continue;
            if (bigger > lower) {
                mid = j;
                bigger--;
                lower ++;
            }
            neighbours[j].first = last;
            neighbours[last].second = j;
            last = j;
        }
        for (int j = n -1 ; j >= i; j -= 1) {
            if (lower == bigger + 1) 
                result += (int64) (j + 1) * (i + 1) * mid;
            int left  = neighbours[element[j]].first;
            int right = neighbours[element[j]].second;
            neighbours[left].second = right;
            neighbours[right].first = left;
            if (element[j] == mid) {
                bigger--;
                mid = right;
            }
            else if (element[j] < mid) 
                lower--;
            else 
                bigger--;
            while (lower > bigger) {
                mid = neighbours[mid].first;
                bigger++;
                lower --;
            }
            while (bigger > lower) {
                mid = neighbours[mid].second;
                bigger--;
                lower ++;
            }
        }
    }
    printf("%lld\n", result);
    return 0;
}


























































