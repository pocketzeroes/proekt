#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef long double ld;
int n,m;
char grid[2000][2000];
int nmark[2],prev;
bool full;
int nlines[2];
int nkey[2][3000][3000];
int dr[] = { 1, 1, 0, -1 },
    dc[] = { 0, 1, 1, 1 };

char get(int r, int c){
  if (r<0 || r>=n || c<0 || c>=n)
     return '.';
  return grid[r][c];
}
void detect(int p, char ch){
  for(int k=(0);k<(4);++k){
    for(int r=(0);r<(n);++r){
      for(int c=(0);c<(n);++c){
        if (get(r-dr[k],c-dc[k]) != ch){
          int len=0;
          while (get(r+len*dr[k],c+len*dc[k]) == ch)
            ++len;
          if (len >= m){
            ++nlines[p];
            for(int i=(0);i<(len);++i){
              if (i<m && m+i >= len){
                ++nkey[p][r+i*dr[k]][c+i*dc[k]];
              }
            }
          }
        }
      }
    }
  }
}
int main(){
  scanf("%d%d", &n, &m);
  for(int i=(0);i<(n);++i)
    for(int j=(0);j<(n);++j)
      scanf(" %c", &grid[i][j]);
  memset(nmark,0,sizeof(nmark));
  full = 1;
  for(int i=(0);i<(n);++i){
    for(int j=(0);j<(n);++j){
      if (grid[i][j] == 'X')
        ++nmark[0];
      else if (grid[i][j] == 'O')
        ++nmark[1];
      else
        full = 0;
    }
  }
  if (nmark[0] == nmark[1])
    prev = 1;
  else if (nmark[0] == nmark[1]+1)
    prev = 0;
  else{
    printf("ERROR\n");
    return 0;
  }
  memset(nlines,0,sizeof(nlines));
  memset(nkey,0,sizeof(nkey));
  for(int p=(0);p<(2);++p){
    detect(p,"XO"[p]);
  }
  if (nlines[1-prev] != 0){
    printf("ERROR\n");
    return 0;
  }
  if (nlines[prev] == 0){
    if (full)
      printf("DRAW\n");
    else
      printf("IN PROGRESS\n");
    return 0;
  }
  bool happy = 0;
  for(int i=(0);i<(n);++i)
    for(int j=(0);j<(n);++j)
      if (nkey[prev][i][j] == nlines[prev])
        happy = 1;
  if (!happy){
    printf("ERROR\n");
    return 0;
  }
  printf("%c WINS\n", "XO"[prev]);
  return 0;
}
