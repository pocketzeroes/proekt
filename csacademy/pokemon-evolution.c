#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int main() {
    long long n, m, x, y;
    scanf("%lld %lld %lld %lld", &n, &m, &x, &y);
    long long left = 0, right = n;
    while (left != right) {
        int mid = (left + right + 1) / 2;
        if (m + (n - mid) * y >= mid * x) 
            left = mid;
        else 
            right = mid - 1;
    }
    printf("%d", left);
}
