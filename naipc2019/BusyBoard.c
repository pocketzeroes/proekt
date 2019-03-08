#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char buff[100000];
bool chk(){
  int r, c;
  scanf("%d %d", &r, &c);
  char*A[r];
  char*B[r];
  for(int z=0; z<r; z++){
    scanf("%s", &buff);
    A[z] = strdup(buff);
  }
  for(int z=0; z<r; z++){
    scanf("%s", &buff);
    B[z] = strdup(buff);
  }
  bool same=1;
  for(int z=0; z<r; z++){
    if(strcmp(A[z], B[z])!=0){
      same=0;
      break;
    }
  }
  if(same)
    return true;
  bool hittable_row[r]; fill(hittable_row, r, 1);
  bool hittable_col[c]; fill(hittable_col, c, 1);
  for(int i=0; i<r; i++){
    int cnt = 0;
    for(int j=0; j<c; j++)
      if(B[i][j] == 'X')
        cnt++;
    if(cnt > 1)
      hittable_row[i] = false;
  }
  for(int j=0; j<c; j++){
    int cnt = 0;
    for(int i=0; i<r; i++)
      if(B[i][j] == 'X')
        cnt++;
    if(cnt > 1)
      hittable_col[j] = false;
  }
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++)
      if(A[i][j] == 'X' && B[i][j] == 'X'){
        if(!hittable_row[i])
          hittable_col[j] = false;
        if(!hittable_col[j])
          hittable_row[i] = false;
      }
  }
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++)
      if(A[i][j] == 'O' && B[i][j] == 'X')
        if(!hittable_row[i] || !hittable_col[j])
          return false;
  }
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++)
      if(A[i][j] == 'X' && B[i][j] == 'O')
        if(!hittable_row[i] && !hittable_col[j])
          return false;
  }
  int AO_cnt = 0,
      BX_cnt = 0;
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++)
      if(hittable_row[i] && hittable_col[j]){
        if(A[i][j] == 'O')
          AO_cnt++;
        if(B[i][j] == 'X')
          BX_cnt++;
      }
  }
  return AO_cnt > 0 && BX_cnt > 0;
}
int main(){
  printf("%d\n", chk());
  return 0;
}
