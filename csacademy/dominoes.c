#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}



int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int dominoes[n];
    for (int i = 0; i < n; ++i) {
        int coord;
        scanf("%d", &coord);
        dominoes[i] = coord;
    }
    int left = 0, right = 0;
    int best = k;
    do {
        while ((dominoes[right] - dominoes[left]) - (right - left) > k)
            ++left;
        best = max(best, right - left + 1 + k);
        right++;
    } 
    while (right < n);
    printf("%d", best);
}
