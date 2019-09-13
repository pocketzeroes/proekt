#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
const ll mod =(ll)1e9+7;
typedef struct{
    ll m[51][51];
}mat;

mat mult(mat a, mat b){
    int resultRow = 51,
        resultCol = 51,
        n         = 51;
    mat product;
    for(int i = 0; i < resultRow; ++i){
        for(int j = 0; j < resultCol; ++j){
            product.m[i][j] = 0;
            for(int k=0; k<n; ++k){
                product.m[i][j] += a.m[i][k] * b.m[k][j];
                product.m[i][j] %= mod;
            }
        }
    }
    return product;
}
mat power(mat matrix, ll b){
    if(b <= 1)
        return matrix;
    mat temp = power(matrix, b/2);
    if(b % 2 == 0)
        return mult(temp, temp);
    return mult(mult(temp, temp), matrix);
}
void solve(){
    int n, k;
    scanf("%d %d", &n, &k);
    mat ways; clr(ways.m);
    for(int i=0; i<50; i++)
        ways.m[i][i+1]++;
    for(int i=0; i<k; i++){
        int t;
        scanf("%d", &t);
        ways.m[t-1][0]++;
    }
    ways = power(ways, n);
    if(ways.m[0][0])
        printf("%lld\n", ways.m[0][0]);
    else
        puts("IMPOSSIBLE");
}
int main(){
    int cases;
    scanf("%d", &cases);
    while(cases--)
        solve();
    return 0;
}
