#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MOD =(int)(1e9) + 7};
int n;
int le[1000][26], ri[1000][26];
int d[1001][1001];

void modAdd(int*x, int y){
   *x += y;
    if(*x >= MOD)
       *x -= MOD;
}
char buff[100000];
int main(){
    char*s;
    scanf("%s", &buff);
    s = strdup(buff);
    n = strlen(s);
    for (int i = 0; i < 26; ++i)
        le[0][i] = -1;
    le[0][s[0] - 'a'] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 26; ++j)
            le[i][j] = le[i - 1][j];
        le[i][s[i] - 'a'] = i;
    }
    for (int i = 0; i < 26; ++i)
        ri[n - 1][i] = n;
    ri[n - 1][s[n - 1] - 'a'] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < 26; ++j)
            ri[i][j] = ri[i + 1][j];
        ri[i][s[i] - 'a'] = i;
    }
    d[0][n] = 1;
    int ans = 0;
    for (int i = 0; i < (n + 1); ++i){
        for (int j = n; j >= i; --j){
            if (d[i][j]) {
                if (i != 0 || j != n)
                    modAdd(&ans, d[i][j]);
                for (int k = 0; k < (int)(26); ++k) {
                    if (ri[i][k] < j) {
                        modAdd(&ans, d[i][j]);
                        if (le[j - 1][k] > ri[i][k])
                            modAdd(&d[ri[i][k] + 1][le[j - 1][k]], d[i][j]);
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}































