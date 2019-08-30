#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int c[52][52];

int main(){
  int N;
  while(scanf("%d", &N)==1){
    memset(c, 0, sizeof(c));
    for(int i = 0; i < N; i++){
      char*s=getstr();
      for (int i = 0; i < 8; i += 2) if (s[i] != '0')
      for (int j = 0; j < 8; j += 2) if (s[j] != '0' && j != i) {
        c[s[i]-'A' + (s[i+1]=='+'?0:26)][s[j]-'A' + (s[j+1]=='+'?26:0)] = true;
      }
    }
    for (int k = 0; k < 52; k++)
    for (int i = 0; i < 52; i++)
    for (int j = 0; j < 52; j++)
      c[i][j] |= (c[i][k] & c[k][j]);
    bool bounded = true;
    for (int i = 0; i < 52; i++)
      if (c[i][i]) bounded = false;
    if (bounded)
      puts("bounded");
    else
      puts("unbounded");
  }
  return 0;
}
