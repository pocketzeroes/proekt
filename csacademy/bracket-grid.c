#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>

typedef long long ll;
enum{ MAX = 222};
char*RES[MAX];
ll DP[MAX][MAX][MAX * 2];

char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}
void calcDP(int n, int m){
    memset(DP, 0, sizeof(DP));
    DP[0][0][1] = 1;
    for(int i = (0); i < (n); i++){
        for(int j = (0); j < (m); j++){
            for(int k = (0); k < (n + m + 1); k++){
                if (DP[i][j][k] == 0) 
                    continue;
                if (i < n - 1){
                    if (RES[i+1][j] == '+') 
                        DP[i+1][j][k+1] += DP[i][j][k];
                    if (k && RES[i+1][j] == '-') 
                        DP[i+1][j][k-1] += DP[i][j][k];
                }
                if (j < m-1){
                    if (RES[i][j+1] == '+') 
                        DP[i][j+1][k+1] += DP[i][j][k];
                    if (k && RES[i][j+1] == '-') 
                        DP[i][j+1][k-1] = DP[i][j][k];
                }
            }
        }
    }
}
int main(){
    int k;
    scanf("%d", &k);
    int n = 199;
    int m = n + 1;
    for(int i = (0); i < (n); i++)
        RES[i] = string(m, '-');
    int x = 0, y = 0;
    RES[0][0] = '+';
    while(k){
        if (k % 2 == 0){
            RES[x+2][y] = '+';
            RES[x][y+2] = '+';
            RES[x+2][y+2] = '+';
            x += 2;
            y += 2;
            k /= 2;
        }
        else{
            int xx = x + 2;
            while(xx < n){
                RES[xx][y] = '+';
                xx += 2;
            }
            xx -= 2;
            if (xx != n-1) 
                assert(!"-1");
            int yy = y;
            while (yy < m){
                RES[xx][yy] = '+';
                yy += 2;
            }
            y += 2;
            RES[x][y] = '+';
            y += 2;
            RES[x][y] = '+';
            k--;
        }
    }
    for(int i = (0); i < (n); i++){
        for(int j = (0); j < (m); j++){
            if (RES[i][j] == '-') 
                RES[i][j] = ')';
            else 
                RES[i][j] = '(';
        }
    }
    printf("%d %d\n", n, m);
    for(int i = (0); i < (n); i++)
        puts(RES[i]);
}
































