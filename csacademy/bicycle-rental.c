#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAX_N   = (int)1e5};
enum{ MAX_VAL = (int)1e5};

int main() {
    int n;
    scanf("%d", &n);
    int best = (int)1e9;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        best = min(best, max(a, b) + c);
    }
    printf("%d\n", best);
}

