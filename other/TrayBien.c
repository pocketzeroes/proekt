#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXCOL = 24};
bool ok[3][MAXCOL+1];
long long table[7][MAXCOL+1];

void initTable(){
  table[0][0] = 1;
  for(int i=1; i<=6; i++)
    table[i][0] = 0;
  for(int r=0; r<3; r++)
    ok[r][0] = false;
  for(int c=1; c<=MAXCOL; c++)
    for(int r=0; r<3; r++)
      ok[r][c] = true;
}
void fillTable(int cols){
  for(int c=1; c<=cols; c++){
    bool horz0 = ok[0][c] && ok[0][c-1];
    bool horz1 = ok[1][c] && ok[1][c-1];
    bool horz2 = ok[2][c] && ok[2][c-1];
    table[0][c] = table[0][c-1];
    if (ok[0][c] && ok[1][c])
      table[0][c] += table[0][c-1];
    if (ok[1][c] && ok[2][c])
      table[0][c] += table[0][c-1];
    if (horz0 && horz1)
      table[0][c] += table[1][c-1];
    if (horz0 && horz2)
      table[0][c] += table[2][c-1];
    if (horz1 && horz2)
      table[0][c] += table[3][c-1];
    if (horz0) {
      table[0][c] += table[6][c-1];
      if (ok[1][c] && ok[2][c])
        table[0][c] += table[6][c-1];
    }
    if (horz1) {
      table[0][c] += table[5][c-1];
    }
    if (horz2) {
      table[0][c] += table[4][c-1];
      if (ok[0][c] && ok[1][c])
        table[0][c] += table[4][c-1];
    }
    if (horz0 && horz1 && horz2)
      table[0][c] += table[0][c-2];
    for(int i=1; i<=6; i++)
      table[i][c] = table[0][c-1];
    if (ok[2][c])
      table[1][c] = table[0][c-1];
    if (ok[1][c])
      table[2][c] = table[0][c-1];
    if (ok[0][c])
      table[3][c] = table[0][c-1];
    if (horz2)
      table[1][c] += table[4][c-1];
    if (horz1)
      table[2][c] += table[5][c-1];
    if (horz0)
      table[3][c] += table[6][c-1];
    if (ok[0][c] && ok[1][c])
      table[4][c] = table[0][c-1];
    if (ok[0][c] && ok[2][c])
      table[5][c] = table[0][c-1];
    if (ok[1][c] && ok[2][c])
      table[6][c] = table[0][c-1];
    if (ok[0][c] && ok[1][c])
      table[4][c] += table[0][c-1];
    if (horz0)
      table[4][c] += table[6][c-1];
    if (horz1)
      table[4][c] += table[5][c-1];
    if (horz0 && horz1)
      table[4][c] += table[1][c-1];
    if (horz0)
      table[5][c] += table[6][c-1];
    if (horz2)
      table[5][c] += table[4][c-1];
    if (horz0 && horz2)
      table[5][c] += table[2][c-1];
    if (ok[1][c] && ok[2][c])
      table[6][c] += table[0][c-1];
    if (horz1)
      table[6][c] += table[5][c-1];
    if (horz2)
      table[6][c] += table[4][c-1];
    if (horz1 && horz2)
      table[6][c] += table[3][c-1];
  }
}
int main(){
  int cols, n;
  scanf("%d %d", &cols, &n);
  initTable();
  int count = 0;
  for(int i=0; i<n; i++){
    double x, y;
    scanf("%lf%lf", &x, &y);
    if(ok[(int)y][(int)x+1]){
      ok[(int)y][(int)x+1] = false;
      count++;
    }
  }
  if(count == cols*3)
    puts("0");
  else{
    fillTable(cols);
    printf("%lld\n", table[0][cols]);
  }
  return 0;
}
