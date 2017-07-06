#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAX_N = (int)1e5};

int n, k;
int A[MAX_N + 1];
int S[MAX_N + 1];

int rangeQuery(int left, int right) {
    return S[right] - S[left-1];
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
        S[i] = S[i - 1] + A[i];
    }
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (A[i] == 0) {
            if (rangeQuery(max(1, i - k), min(n, i + k)) < 2) {
                count += 1;
            }
        }
    }
    printf("%d\n", count);
}
