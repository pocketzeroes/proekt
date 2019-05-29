#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLENOPERAND 20
#define EMPTYPOS 10
#define UNDEFCHAR '*'
#define UNDEFVAL -1

typedef struct letravalor{
  char letra;
  int valor;
} SOLC;


SOLC Solucao[11] = {
  {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL},
  {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL},
  {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,UNDEFVAL},
  {UNDEFCHAR,UNDEFVAL}, {UNDEFCHAR,0}};


int DigitoVisitado[10] = {0};  
int NLetras;
int Problem[10][MAXLENOPERAND+1]; 
int Length[10];

int resolve(int row, int column, int last, int carry, int n);
int last_row(int column, int last, int carry, int n);
int posicao(char c);
int soma_coluna(int column,int carry,int nr);
int min_left(int row,int column,int n);

int posicao(char c) {
  int i;
  for(i=0; i< NLetras; i++)
    if (Solucao[i].letra == c)
      return i;
  Solucao[NLetras++].letra = c;
  return NLetras-1;
}
int main(){
  int j, n, i, numsols = 0, maxlen; 
  char linha[MAXLENOPERAND+2];
  Solucao[EMPTYPOS].valor = 0;
  for (i=0; i< 10; i++)   
    Solucao[i].valor = UNDEFVAL;
  scanf("%d",&n);
  NLetras = 0;
  for (i=0; i<n;i++) {
    scanf("%s",linha);
    Length[i] = (int) strlen(linha);    
    for(j=0; linha[j] != '\0'; j++) 
      Problem[i][Length[i]-1-j] = posicao(linha[j]);
    for(; j < MAXLENOPERAND+1; j++) 
      Problem[i][j] = EMPTYPOS;
  }
  maxlen = 0;
  for (i=0; i <n-1; i++)
    if (Length[i] > maxlen)
      maxlen = Length[i];
  if (Length[n-1] > maxlen+1)
    return 0;
  if (Length[n-1] > maxlen)
    maxlen = Length[n-1];
  numsols = resolve(0,0,maxlen-1,0,n); 
  printf("%d\n",numsols);
  return 0;
}
int soma_coluna(int column,int carry,int nr){
  int i,  sum = carry;
  for (i=0; i < nr; i++) 
    sum += Solucao[Problem[i][column]].valor;
  return sum;
}
#ifdef DEBUG_PRINTSOLS
void escreve_sol(){
  int i;
  for (i=0; i< NLetras; i++)
    printf("(%c,%d) ",Solucao[i].letra,Solucao[i].valor);
  putchar(10);
}
#endif
int last_row(int column, int last, int carry, int n) {
  int d, sols, soma;
  soma = soma_coluna(column,carry,n-1);
  d = soma % 10;
  if (d == 0 && min_left(n-1,column,n) != 0)
    return 0; 
  if (Solucao[Problem[n-1][column]].valor != UNDEFVAL) {
    if (d != Solucao[Problem[n-1][column]].valor) 
      return 0;
    if (column != last) 
      return resolve(0,column+1,last,soma/10,n);
    if (soma/10 != 0) 
      return 0;  
#ifdef DEBUG_PRINTSOLS
    escreve_sol();
#endif
    return 1; 
  }
  else { 
    if (DigitoVisitado[d]) 
      return 0;
    if (column == last) {
      if (soma/10 != 0) 
	return 0;  
#ifdef DEBUG_PRINTSOLS
      Solucao[Problem[n-1][column]].valor = d;
      escreve_sol();
      Solucao[Problem[n-1][column]].valor = UNDEFVAL;
#endif
      return 1;
    }
    DigitoVisitado[d] = 1;
    Solucao[Problem[n-1][column]].valor = d;
    sols = resolve(0,column+1,last,soma/10,n);
    DigitoVisitado[d] = 0;
    Solucao[Problem[n-1][column]].valor = UNDEFVAL;
    return sols;
  }
}
int resolve(int row, int column, int last, int carry, int n) {
  int d, dmin, sols;
  if (row == n-1) 
    return last_row(column,last,carry,n);
  if (Solucao[Problem[row][column]].valor != UNDEFVAL) 
    return resolve(row+1,column,last,carry,n);
  sols = 0;
  dmin = min_left(row,column,n);
  for (d=dmin; d < 10; d++)
    if (!DigitoVisitado[d]) {
      DigitoVisitado[d] = 1;
      Solucao[Problem[row][column]].valor = d;
      sols += resolve(row+1,column,last,carry,n);
      Solucao[Problem[row][column]].valor = UNDEFVAL;
      DigitoVisitado[d] = 0;
    }
  return sols;
}
int min_left(int row,int column,int n) {
  int i = 0;
  if (column == Length[row]-1)
    return 1;
  for(i=0; i< n; i++)
    if (Problem[row][column] == Problem[i][Length[i]-1])
      return 1;
  return 0;
}
