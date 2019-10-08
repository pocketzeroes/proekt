#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long   ll;
typedef long double ld;

int main(){
    int P, D, d;
    ll a, b;
    scanf("%d%d", &P, &D);
    ll vA[D];
    ll vB[D];
    ll wA;
    ll wB;
    ll wdiff  = 0;
    ll vtotal = 0;
    bool Awins;
    for(int i = 0; i < D; i++){
        vA[i] = 0;
        vB[i] = 0;
    }
    for(int i = 0; i < P; i++){
        scanf("%d %lld %lld", &d, &a, &b);
        vA[d - 1] += a;
        vB[d - 1] += b;
        vtotal += a + b;
    }
    for(int i = 0; i < D; i++){
        if(vA[i] > vB[i]){
            Awins = true;
            wB = vB[i];
            wA = vA[i] - ((ll) floor(((ld) vA[i] + vB[i]) / 2.0)) - 1;
        }
        else{
            Awins = false;
            wA = vA[i];
            wB = vB[i] - ((ll) floor(((ld) vA[i] + vB[i]) / 2.0)) - 1;
        }
        wdiff += (wA - wB);
        printf("%c %lld %lld\n", (Awins ? 'A' : 'B'), wA, wB);
    }
    printf("%.8Lf\n", fabsl((ld) wdiff) / ((ld) vtotal) );
    return 0;
}
