#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

//////////////////
int  r;
int  c;
int  p;
int  sum;
int**grid;
int* inverses;

int*solveEqn(int**eqns){
    int n = r*c;
    bool skippedRows[n]; clr(skippedRows);
    for(int i=0; i<n; i++){
        int move = eqns[i][i] == 0 ? -1 : i;
        for(int j=i+1; j<n; j++) {
            if(eqns[j][i] != 0) {
                if(move == -1) 
                    move = j;
            }
        }
        if (move == -1) {
            skippedRows[i] = true;
            continue;
        }
        int*tmp = eqns[i];
        eqns[i] = eqns[move];
        eqns[move] = tmp;
        int mult = inverses[eqns[i][i]];
        for (int j=i; j<=n; j++)
            eqns[i][j] = (eqns[i][j]*mult)%p;
        for (int j=i+1; j<n; j++) {
            mult = eqns[j][i];
            for (int k=i; k<=n; k++)
                eqns[j][k] = (eqns[j][k] - mult*eqns[i][k] + p*p)%p;
        }
    }
    int*resu = calloc(n, sizeof(int));
    for(int i=n-1; i>=0; i--){
        if(!skippedRows[i]){
            int sub = 0;
            for(int j=i+1; j<n; j++)
                sub = (sub + resu[j]*eqns[i][j])%p;
            resu[i] = (eqns[i][n]-sub+p)%p;
        }
        else{
            int lhs = 0;
            for(int j=0; j<n; j++)
                lhs = (lhs + resu[j]*eqns[i][j])%p;
            if(lhs%p != eqns[i][n]%p)
                return NULL;
        }
    }
    return resu;
}
void solveDegenerate(){
    int**eqns = newmat(r*c, r*c+1);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            for(int k=0; k<c; k++)
                eqns[c*i+j][c*i+k] = 1;
            for(int k=0; k<r; k++)
                eqns[c*i+j][c*k+j] = 1;
            eqns[c*i+j][r*c] = grid[i][j];
        }
    }
    int*res = solveEqn(eqns);
    if(res == NULL)
        puts("-1");
    else{
        int numToggle = 0;
        for(int i=0; i<r*c; i++)
            numToggle += res[i];
        printf("%d\n", numToggle);
        bool flag = false;
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                for(int k=0; k<res[c*i+j]; k++){
                    if(flag)
                        printf(" ");
                    printf("%d", c*i+j+1);
                    flag = true;
                }
            }
        }
        puts("");
    }
}
void solve(){
    int sumAll = (sum*inverses[(r+c-1)%p])%p;
    int sumR[r]; clr(sumR);
    for(int i=0; i<r; i++){
        int RHS = 0;
        for(int j=0; j<c; j++)
            RHS = (RHS + grid[i][j])%p;
        RHS = (RHS - sumAll + p)%p;
        sumR[i] = (inverses[(c-1)%p]*RHS)%p;
    }
    int sumC[c]; clr(sumC);
    for(int i=0; i<c; i++){
        int RHS = 0;
        for(int j=0; j<r; j++)
            RHS = (RHS + grid[j][i])%p;
        RHS = (RHS - sumAll + p)%p;
        sumC[i] = (inverses[(r-1)%p]*RHS)%p;
    }
    int rez[r][c];
    int total = 0;
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            rez[i][j] = (sumR[i] + sumC[j] - grid[i][j] + p)%p;
            total += rez[i][j];
        }
    }
    printf("%d\n", total);
    bool flag = false;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            for(int k=0; k<rez[i][j]; k++){
                if(flag)
                    printf(" ");
                printf("%d", c*i+j+1);
                flag = true;
            }
        }
    }
    puts("");
}
int main(){
    r = in_nextInt();
    c = in_nextInt();
    p = in_nextInt();
    inverses = calloc(p, sizeof(int));
    inverses[0] = 0;
    for(int i=1; i<p; i++)
        for(int j=1; j<p; j++)
            if((i*j)%p == 1)
                inverses[i] = j;
    grid = newmat(r, c);
    sum = 0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            grid[i][j] = p - in_nextInt();
            sum = (sum +grid[i][j])%p;
        }
    }
    if((r+c-1)%p == 0 && sum != 0)
        puts("-1");
    else if((r+c-1)%p == 0 || (r-1)%p == 0 || (c-1)%p == 0)
        solveDegenerate();
    else
        solve();
    return 0;
}
