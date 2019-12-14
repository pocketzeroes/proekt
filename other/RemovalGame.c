#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ SIZE = 100};

typedef struct{
    int cost, k, best;
}tabentry;
tabentry table[SIZE][SIZE];
int vals[SIZE];

int gcd(int a, int b){
    if(b==0)
        return a;
    else
        return gcd(b, a%b);
}

int main(){
    int n, icase=0;
    scanf("%d", &n);
    while (n > 0){
        for(int i=0; i<n; i++)
            scanf("%d", &vals[i]);
        for(int i=0; i<n; i++) {
            table[i][0].cost = 0;
            table[i][0].k    =-2;
        }
        for(int i=0; i<n-1; i++) {
            table[i][1].cost = 0;
            table[i][1].k    =-2;
        }
        table[n-1][1].cost = 0;
        table[n-1][1].k    =-2;
        for(int i=0; i<n; i++){
            table[i][2].cost = gcd(vals[i], vals[(i+2)%n]);
            table[i][2].k = -1;
        }
        for(int len = 3; len<n; len++){
            for(int i=0; i<n; i++){
                int best = 100000000;
                int savek;
                for(int k=1; k<len; k++){
                    int tmp = table[i][k].cost + table[(i+k)%n][len-k].cost;
                    if (tmp < best){
                        best = tmp;
                        savek = k;
                    }
                }
                int final = gcd(vals[i], vals[(i+len)%n]);
                if (len == n-1){
                    int tmp = gcd(vals[i], vals[(i+savek)%n]);
                    if(tmp < final)
                       final = tmp;
                    tmp = gcd(vals[(i+savek)%n], vals[(i+len)%n]);
                    if(tmp < final)
                       final = tmp;
                }
                table[i][len].best = final;
                table[i][len].cost = final + best;
                table[i][len].k    = savek;
            }
        }
        if(n == 2)
            printf("%d\n", gcd(vals[0], vals[1]));
        else if (n==3){
            int k=0;
            for(int i=1; i<3; i++)
                if (table[i][2].cost < table[k][2].cost)
                    k=i;
            printf("%d\n", 2*table[k][2].cost);
        }
        else{
            int k = 0;
            for(int i=1; i<n; i++){
                if (table[i][n-1].cost + table[i][n-1].best < table[k][n-1].cost+table[k][n-1].best)
                    k = i;
            }
            printf("%d\n", table[k][n-1].cost +table[k][n-1].best);
        }
        scanf("%d", &n);
    }
    return 0;
}
