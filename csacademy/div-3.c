#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

enum{ inf =(int) 1e9};

int Greedy(int x) {
    if (x == 2) {
        return 1;
    } else if (x == 1) {
        return 0;
    }
    if (x % 3 == 0) {
        return 1 + Greedy(x / 3);
    } else if (x % 3 == 1) {
        return 1 + Greedy(x - 1);
    } else {
        return 1 + Greedy(x + 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", Greedy(n) );
    return 0;
}
