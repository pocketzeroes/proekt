#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long int64;

int64 min(int64 a,int64 b){return a<b?a:b;}
int64 max(int64 a,int64 b){return a>b?a:b;}


enum{ kMaxVal =(int) 1e6};
int64 primeHash[kMaxVal+1];
int64 inversePrimeHash[kMaxVal+1];
int count[2][kMaxVal+1];


void Init() {
    bool prime[kMaxVal];
    for(int i=0;i<kMaxVal;i++)prime[i]=true;
    for (int i = 1; i <= kMaxVal; i++){
        primeHash[i] = 1;
        inversePrimeHash[i] = 1;
    }
    for (int p = 2; p <= kMaxVal; p += 1) {
        if (!prime[p]) {
            continue;
        }
        for (int el = p; el < kMaxVal; el += p) {
            prime[el] = false;
            int x = el / p, pExponent = 1;
            while (x % p == 0) {
                x /= p;
                pExponent += 1;
            }
            pExponent %= 3;
            if (pExponent == 0) {
                continue;
            }
            if (pExponent == 1) {
                primeHash[el] *= p;
		        inversePrimeHash[el] *= 1LL * p * p;
            }
            else {
                primeHash[el] *= 1LL * p * p;
                inversePrimeHash[el] *= p;
            }
        }
    }
    for (int i = 0; i <= kMaxVal; i += 1) {
        if (inversePrimeHash[i] > kMaxVal) {
            inversePrimeHash[i] = 0;
        }
    }
}
int main() {
    Init();
    int numTestcases;
    scanf("%d", &numTestcases);
    while(numTestcases--){
        int n, m;
        scanf("%d %d", &n, &m);
        int elementsA[n];
        int elementsB[m];
        for (int i = 0; i < n; i += 1) {
            int a; 
            scanf("%d", &a);
            count[0][primeHash[a]] += 1;
            elementsA[i] = a;
        }
        for (int i = 0; i < m; i += 1) {
            int b; 
            scanf("%d", &b);
            count[1][primeHash[b]] += 1;
            elementsB[i] = b;
        }
        int64 maxResult = -1;
        for(int i=0;i<n;i++){ int a = elementsA[i];
            int primeHashCnt = count[0][primeHash[a]];
            int inversePrimeHashCnt = count[1][inversePrimeHash[a]];
            if (primeHashCnt == 0 || inversePrimeHashCnt == 0){
                continue;
            }
            int64 currentResult = 1LL * primeHashCnt * primeHashCnt + 1LL * inversePrimeHashCnt * inversePrimeHashCnt;
            maxResult = max(maxResult, currentResult);
        }
        printf("%lld\n", maxResult);
        for(int i=0;i<n;i++){ int itr = elementsA[i];
            count[0][primeHash[itr]] -= 1;
        }
        for(int i=0;i<m;i++){ int itr = elementsB[i];
            count[1][primeHash[itr]] -= 1;
        }
    }
    return 0;
}




























































