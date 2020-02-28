#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define RFOR(i, b, a) for (int i = (b)-1; i >= (a); --i)
#define FILL(A, value) memset(A, value, sizeof(A))
#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
typedef long long Int;
typedef unsigned long long UInt;
enum{ INF = 1000000000};

int main(){
    int n;
    scanf("%d", &n);
    int A[n];
    int B[n];
    FOR(i,0,n)
        scanf("%d", &A[i]);
    FOR(i,0,n)
        scanf("%d", &B[i]);
    int res = 0;
    FOR(i,0,n){
        int val = INF;
        FOR(j,0,n){
            val = fmin(val, abs(A[i] - B[j]));
        }
        res = fmax(res, val);
    }    
    printf("%d\n", res);
    return 0;
}
