#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll table_B[505][505];
ll table_LNR[505][505];
ll table_RNL[505][505];
int x[505];

int gcd(int a, int b) {
    if (a==0)
        return b;
    return gcd (b % a, a);
}
bool compat(int x, int y){
    return gcd(x,y) != 1;
}
ll modp(ll x) {return (x % 1000000007);}
ll count_B(int i, int j);
ll count_RNL(int i, int j);
ll count_LNR(int i, int j);
ll count_A(int i, int j);
ll count_L(int i, int j);

ll count_B(int i, int j){
    ll answer = 0;
    if (table_B[i][j] >= 0)
        return table_B[i][j];
    for (int k=i+1; k<=j-1; k++){
    if(compat(x[k], x[j]))
        answer = modp(answer + count_L(i,k) * count_A(k,j));
    }
    table_B[i][j] = answer;
    return answer;
}
ll count_RNL(int i, int j){
    ll answer = 0;
    if (table_RNL[i][j] >= 0)
        return table_RNL[i][j];
    if (i+1 == j)
        answer = 1;
    else {
        for (int k=i+1; k<=j-1; k++) {
            if(compat(x[k], x[j]))
                answer = modp(answer + count_RNL(i,k) * count_A(k,j));
        }
    }
    table_RNL[i][j] = answer;
    return answer;
}
ll count_LNR(int i, int j){
    ll answer = 0;
    if (table_LNR[i][j] >= 0)
        return table_LNR[i][j];
    if (i+1 == j)
        answer = 1;
    else {
        for (int k=i+1; k<=j-1; k++) {
            if(compat(x[i], x[k]))
                answer = modp(answer + count_A(i,k) * count_LNR(k,j));
        }
    }
    table_LNR[i][j] = answer;
    return answer;
}
ll count_A(int i, int j){
    if (i+1 == j)
        return 1;
    else
        return (modp (count_B(i,j) + count_LNR(i,j) + count_RNL(i,j)));
}
ll count_L(int i, int j){
    if (i+1 == j)
        return 0;
    else
        return (modp (count_B(i,j) + count_LNR(i,j)));
}
int main(){
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%d", &x[i]);
    }
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=n; j++) {
            table_B[i][j] = table_LNR[i][j] = table_RNL[i][j] = -1;
        }
    }
    printf("%lld\n", count_LNR(0,n));
    return 0;
}
