#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef long long ll;

enum{ N =(int)1e5 + 10};
int n, neg[N], pos[N], numNeg, numPos;
ll sumPos[N], sumNeg[N];

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; ++i){
        int x;
        scanf("%d", &x);
        if(x < 0)
            neg[++numNeg] = -x;
        else if(x > 0)
            pos[++numPos] = x;
    }
    qsort(pos+1, numPos, sizeof(int), cmp);
    qsort(neg+1, numNeg, sizeof(int), cmp);
    for(int i=1; i<=numPos; ++i)
        sumPos[i] = sumPos[i - 1] + pos[i];
    for(int i=1; i<=numNeg; ++i)
        sumNeg[i] = sumNeg[i - 1] + neg[i];
    ll ans = sumPos[numPos];
    for(int i=0; i<numPos; ++i){
        int mid = (numPos + (i + 1)) / 2;
        ans = fminl(ans, sumPos[i] + (ll)pos[mid] * (mid - (i + 1)) - (sumPos[mid - 1] - sumPos[i]) + sumPos[numPos] - sumPos[mid] - (ll)pos[mid] * (numPos - mid));
    }
    ans += sumNeg[numNeg];
    for(int i=0; i<numNeg; ++i){
        int mid = (numNeg + (i + 1)) / 2;
        ans = fminl(ans, sumNeg[i] + (ll)neg[mid] * (mid - (i + 1)) - (sumNeg[mid - 1] - sumNeg[i]) + sumNeg[numNeg] - sumNeg[mid] - (ll)neg[mid] * (numNeg - mid) + sumPos[numPos]);
    }
    printf("%lld\n", ans);
    return 0;
}
