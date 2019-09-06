#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum{ MAXN   = 20};
enum{ MAXVAL = 10};
int m,n,k;
int board    [MAXN][MAXN];
int tileavail[MAXVAL][MAXVAL];
int sol_written;

const char dirchar[7] = " u] [n";

int notcovered(int r, int c){
  if(board[r][c]>=0 && board[r][c]<=9) return 1; else return 0;
}
int inside(int r, int c){
  if(r>=0 && r<m && c>=0 && c<n) return 1; else return 0;
}
int countpossibilities(int r, int c){
  int ret, rdif, cdif;
  ret = 0;
  for(rdif=-1; rdif<=1; rdif++)
    for(cdif=-1; cdif<=1; cdif++)
      if(abs(rdif+cdif)==1)
        if(inside(r+rdif, c+cdif) && notcovered(r+rdif,c+cdif))
          if(tileavail[board[r][c]][board[r+rdif][c+cdif]])
            ret++;
  return ret;
}
int bt(){
  int minr=-1,minc=-1,min=-1,tmp;
  int r,c,rdif, cdif;
  int undo[2], ret=0;
  for(r=0;r<m;r++) for(c=0;c<n;c++)
    if(notcovered(r,c)){
      tmp = countpossibilities(r,c);
      if(min==-1 || min>tmp) { min = tmp; minr = r; minc = c; }
    }
  if(min==-1){
    if(sol_written)
      return 1;
    sol_written = 1;
    for(r=0;r<m;r++){
      for(c=0;c<n;c++){
        if(board[r][c]==-1) putchar('X');
        else putchar(dirchar[board[r][c]-10]);
      }
      printf("\n");
    }
    return 1;
  }
  if(min==0) return 0;
  for(rdif=-1; rdif<=1; rdif++) for(cdif=-1; cdif<=1; cdif++)
    if(abs(rdif+cdif)==1)
      if(inside(minr+rdif, minc+cdif) && notcovered(minr+rdif,minc+cdif))
        if(tileavail[board[minr][minc]][board[minr+rdif][minc+cdif]]){
          undo[0] = board[minr][minc]; undo[1] = board[minr+rdif][minc+cdif];
          tileavail[undo[0]][undo[1]] = tileavail[undo[1]][undo[0]] = 0;
          board[minr][minc] = 10+2*(1+rdif)+1+cdif;
          board[minr+rdif][minc+cdif] = 10+2*(1-rdif)+1-cdif;
          ret += bt();
          board[minr][minc] = undo[0]; board[minr+rdif][minc+cdif] = undo[1];
          tileavail[undo[0]][undo[1]] = tileavail[undo[1]][undo[0]] = 1;
        }
  return ret;
}
int main(){
  int i,j,tmp, tmp2;
  char tmpc;
  while(1){
    scanf(" %d %d %d ", &m, &n, &k);
    if(m==0 && n==0 && k==0) 
      break;
    assert(m<=MAXN && n<=MAXN);
    for(i=0;i<MAXVAL;i++) for(j=0;j<MAXVAL;j++) tileavail[i][j] = 0;
    for(i=0;i<k;i++){
      scanf(" %d %d ", &tmp, &tmp2);
      assert(tmp>=0 && tmp<=9); assert(tmp2>=0 && tmp2<=9);
      tileavail[tmp][tmp2] = tileavail[tmp2][tmp] = 1;
    }
    tmp = m*n-2*k;
    for(i=0;i<m;i++) for(j=0;j<n;j++){
      scanf(" %c ", &tmpc);
      assert(tmpc == 'X' || (tmpc>='0' && tmpc<='9'));
      if(tmpc=='X') { board[i][j] =-1; tmp--; } else board[i][j] = tmpc-'0';
    }
    assert(tmp==0);
    sol_written = 0;
    tmp = bt();
    if(tmp==0) printf("impossible\n");
    else printf("%d\n", tmp-1);
    printf("\n");
  }
  return 0;
}
