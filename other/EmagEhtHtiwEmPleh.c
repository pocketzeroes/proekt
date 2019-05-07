#include<stdio.h>
#include<string.h>

char sol  [8][8];
char white[1000];
char black[1000];

void decp(char *p, int uc){
  char ach;
  int row, col;
  if (strlen(p) == 2)
    ach = 'P';
  else{
    ach = *p;
    p++;
  }
  if (!uc)
    ach = ach + 'a' - 'A';
  row = p[1]-'1';
  col = p[0]-'a';
  sol[row][col] = ach;
}
void decode(char *p, int uc){
  char act[100];
  char *q, *a;
  while (1){
    q = p;
    a = act;
    while (*q && *q!=',')
      *a++ = *q++;
    *a = 0;
    decp(act,uc);
    if (!*q)
      return;
    p = q + 1;
  }
}
int main(){
  int row = 7,i,j;
  gets(white);
  gets(black);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      sol[i][j] = ((i + j) & 1) ? '.' : ':';
  decode (white + 7, 1);
  decode (black + 7, 0);
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  row--;
  printf ("+---+---+---+---+---+---+---+---+\n");
  printf ("|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|:%c:|.%c.|\n", sol[row][0], sol[row][1], sol[row][2], sol[row][3], sol[row][4], sol[row][5], sol[row][6], sol[row][7]);
  printf ("+---+---+---+---+---+---+---+---+\n");
  return 0;
}
