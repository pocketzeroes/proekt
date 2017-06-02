#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

long long num_ap[40];

char Solve(int n, int k) {
    if (num_ap[n] < k) {
        puts("-1");
        exit(0);
    }
    if (n == 0) {
        return 'a';
    } else if (n == 1) {
        return 'b';
    } else if (n == 2) {
        return 'c';
    }
    for (int i = 1; i <= 3; i += 1) {
        if (k > num_ap[n - i]) {
            k -= num_ap[n - i];
        } else {
            return Solve(n - i, k);
        }
    }
}

int main() {
    int n, k; 
    scanf("%d %d", &n, &k);
    num_ap[0] = 1;
    num_ap[1] = 1;
    num_ap[2] = 1;
    for (int i = 3; i <= n; i += 1) {
        num_ap[i] = num_ap[i - 1] + num_ap[i - 2] + num_ap[i - 3];
    }
    printf("%c\n", Solve(n, k) );
    return 0;
}
