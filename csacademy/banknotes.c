#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define ll long long

int banknotes(int A, int B, int S, int N) {
    ll a = A;
    ll b = B;
    ll s = S;
    ll n = N;
    if (a * n == s) return n;
    if (b * n == s) return 0;
    if (a == b) return -1;
    ll aux1 = s - a * n;
    ll aux2 = b - a;
    if (aux1 < 0) {
        aux1 *= -1;
        aux2 *= -1;
    }
    if (aux2 < 0) return -1;
    if (aux1 % aux2 != 0) return -1;
    ll y = aux1 / aux2;
    ll x = n - y;
    if (x < 0) return -1;
    if (a * x + b * y != s) return -1;
    return x;
}

int main() {
    int A, B, S, N;
    scanf("%d %d %d %d", &A, &B, &S, &N);
    printf("%d\n", banknotes(A, B, S, N) );
    return 0;
}
