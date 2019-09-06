#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int sy, sx;
char grid[22][22];
int lenH[22][22], lenV[22][22];
int uH[22][22], uV[22][22];
int n;
char word[200][22];
int len[200];
int i, j, k;
char tmp[22];

void swap(int*nums, int i, int j){
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
bool rec(int i){
  if (i == n) {
    for (j = 0; j < sy; j++) {
      printf("%s\n", grid[j]);
    }
    return 1;
  }
  bool chg[21];
  for (int y = 0; y < sy; y++) {
    for (int x = 0; x + len[i] - 1 < sx; x++) {
      if (lenH[y][x] == len[i] && !uH[y][x]) {
        for (j = 0; j < len[i]; j++) {
          if (grid[y][x + j] != '.' && grid[y][x + j] != word[i][j]) break;
        }
        if (j == len[i]) {
          memset(chg, 0, sizeof chg);
          for (j = 0; j < len[i]; j++)
            if (grid[y][x + j] == '.') {
              grid[y][x + j] = word[i][j];
              chg[j] = 1;
            }
          uH[y][x] = 1;
          if (rec(i + 1)) return 1;
          uH[y][x] = 0;
          for (j = 0; j < len[i]; j++) {
            if (chg[j]) {
              grid[y][x + j] = '.';
            }
          }
        }
      }
    }
  }
  for (int y = 0; y + len[i] - 1 < sy; y++) {
    for (int x = 0; x < sx; x++) {
      if (lenV[y][x] == len[i] && !uV[y][x]) {
        for (j = 0; j < len[i]; j++)
          if (grid[y + j][x] != '.' && grid[y + j][x] != word[i][j]) break;
        if (j == len[i]) {
          memset(chg, 0, sizeof chg);
          for (j = 0; j < len[i]; j++) {
            if (grid[y + j][x] == '.') {
              grid[y + j][x] = word[i][j];
              chg[j] = 1;
            }
          }
          uV[y][x] = 1;
          if (rec(i + 1)) return 1;
          uV[y][x] = 0;
          for (j = 0; j < len[i]; j++) {
            if (chg[j]) {
              grid[y + j][x] = '.';
            }
          }
        }
      }
    }
  }
  return 0;
}
int main() {
  scanf("%d%d\n", &sy, &sx);
  for (i = 0; i < sy; i++) {
    scanf("%s\n", &grid[i]);
  }
  scanf("%d\n", &n);
  for (i = 0; i < n; i++) {
    scanf("%s\n", &word[i]);
    len[i] = strlen(word[i]);
  }
  for (i = 0; i < n; i++) {
    for (j = 1; j < n; j++) {
      if (len[j - 1] < len[j]) {
        swap(len, j-1, j);
        memcpy(tmp, word[j - 1], sizeof tmp);
        memcpy(word[j - 1], word[j], sizeof tmp);
        memcpy(word[j], tmp, sizeof tmp);
      }
    }
  }
  for (i = 0; i < sy; i++) {
    for (j = 0; j < sx; j++) {
      if (grid[i][j] == '.') {
        for (k = j + 1; k < sx && grid[i][k] == '.'; k++)
          ;
        lenH[i][j] = k - j;
        j = k;
      }
    }
  }
  for (i = 0; i < sx; i++) {
    for (j = 0; j < sy; j++) {
      if (grid[j][i] == '.') {
        for (k = j + 1; k < sy && grid[k][i] == '.'; k++)
          ;
        lenV[j][i] = k - j;
        j = k;
      }
    }
  }
  rec(0);
  return 0;
}
