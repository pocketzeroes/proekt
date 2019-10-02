#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
char c[26];

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
ll in_nextLong(){
  ll x;
  scanf("%lld", &x);
  return x;
}
char**newmat(int x, int y){
  char**rv = calloc(x, sizeof(char*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(char));
  return rv;
}
////////////////////////
enum{ STEPS_LIMIT = 50001};

ll*getDiffBySteps(ll numOfSteps){
    ll delta_row = (numOfSteps + 1) / 2;
    if ((delta_row & 1) != 0)
        delta_row = -delta_row;
    ll delta_col = 2 * (((numOfSteps / 2) + 1) / 2);
    if (((numOfSteps / 2) & 1) == 0)
        delta_col = -delta_col;
    ll*rv=calloc(2, sizeof(ll));
    rv[0]=delta_row;
    rv[1]=delta_col;
    return rv;
}
void simulate(int m, int n, int row, int col, ll numOfSteps, char**g){
    int dir = 0;
    int stepSize = 1;
    int typeLimit = fmax(m, n) + 1;
    for (int step = 0; step < numOfSteps; step++){
        char color = c[step % 26];
        if (step <= typeLimit){
            for (int i = 0; i < stepSize; i++){
                g[row][col] = color;
                row += dr[dir];
                if (row < 0)
                    row = m - 1;
                if (row == m)
                    row = 0;
                col += dc[dir];
                if (col < 0)
                    col = n - 1;
                if (col == n)
                    col = 0;
            }
        } 
        else{
            switch (dir) {
              case 0:
                row = ((row - stepSize) % m + m) % m;
                for (int i = 0; i < m; i++) {
                    g[i][col] = color;
                }
                break;
              case 1:
                col = (col + stepSize) % n;
                for (int i = 0; i < n; i++) {
                    g[row][i] = color;
                }
                break;
              case 2:
                row = (row + stepSize) % m;
                for (int i = 0; i < m; i++) {
                    g[i][col] = color;
                }
                break;
              case 3:
                col = ((col - stepSize) % n + n) % n;
                for (int i = 0; i < n; i++) {
                    g[row][i] = color;
                }
                break;
            }
        }
        dir = (dir + 1) & 3;
        stepSize++;
    }
    g[row][col] = '@';
}
void backFill(int m, int n, int row, int col, ll numOfSteps, char**g){
    ll*diff = getDiffBySteps(numOfSteps);
    int dir = (int) ((numOfSteps - 1) & 3);
    dir = (dir + 2) & 3; 
    int toCover = m * n - 1;
    row = (int) (((row + diff[0]) % m + m) % m);
    col = (int) (((col + diff[1]) % n + n) % n);
    g[row][col] = '@';
    while (toCover > 0 && numOfSteps > 0) {
        char color = c[(int) ((numOfSteps - 1) % 26)];
        switch (dir) {
          case 0:
            row = (int) (((row - numOfSteps) % m + m) % m);
            for (int i = 0; i < m; i++) {
                if (g[i][col] == '.') {
                    toCover--;
                    g[i][col] = color;
                }
            }
            break;
          case 1:
            col = (int) ((col + numOfSteps) % n);
            for (int i = 0; i < n; i++) {
                if (g[row][i] == '.') {
                    toCover--;
                    g[row][i] = color;
                }
            }
            break;
          case 2:
            row = (int) ((row + numOfSteps) % m);
            for (int i = 0; i < m; i++) {
                if (g[i][col] == '.') {
                    toCover--;
                    g[i][col] = color;
                }
            }
            break;
          case 3:
            col = (int) (((col - numOfSteps) % n + n) % n);
            for (int i = 0; i < n; i++) {
                if (g[row][i] == '.') {
                    toCover--;
                    g[row][i] = color;
                }
            }
            break;
        }
        numOfSteps--;
        dir = (dir + 3) & 3;
    }
}
int main(){
    for (char cc = 'A'; cc <= 'Z'; cc++)
        c[cc - 'A'] = cc;
    int m   = in_nextInt();
    int n   = in_nextInt();
    int row = in_nextInt()-1;
    int col = in_nextInt()-1;
    ll numOfSteps = in_nextLong();
    char**g=newmat(m, n+1);
    for(int i=0; i<m; i++)
        memset(g[i], '.', n);
    if(numOfSteps < STEPS_LIMIT)
        simulate(m, n, row, col, numOfSteps, g);
    else
        backFill(m, n, row, col, numOfSteps, g);
    for(int i=0; i<m; i++)
        puts(g[i]);
    return 0;
}
