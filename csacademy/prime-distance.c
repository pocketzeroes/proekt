#include <stdio.h>


int Gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return Gcd(b, a % b);
}

int NumPrimes(int n) {
    int ans = 0;
    for (int i = 2; i * i <= n; i += 1) {
        while (n % i == 0) {
            n /= i;
            ans += 1;
        }
    }
    return ans + (n != 1);
}
int main() {
    int a, b; 
    scanf("%d %d", &a, &b);
    int g = Gcd(a, b);
    a /= g;
    b /= g;
    printf("%d", NumPrimes(a) + NumPrimes(b) );
    return 0;
}
