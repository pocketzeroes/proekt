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

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    int r, c;
    scanf("%d %d", &r, &c);
    char*g[r];
    bool row[r]; memset(row, 0, sizeof(row));
    bool col[c]; memset(col, 0, sizeof(col));
    for (int i = 0; i < r; ++i){
      g[i] = getstr();
      for(int j = 0; j < c; ++j)
        if(g[i][j] == '1')
          row[i] = col[j] = true;
    }
    int nr = 0, nc = 0;
    for(int i=0; i<r; i++) if(row[i]) ++nr;
    for(int i=0; i<c; i++) if(col[i]) ++nc;
    char fill = (nr == 1 || nc == 1) ? 'P' : 'I';
    bool ok = true;
    for(int i = 0; i < r; ++i){
      for(int j = 0; j < c; ++j){
        ok &= (!row[i] || !col[j] || g[i][j] == '1');
        g[i][j] = (g[i][j] == '0' ? 'N' : fill);
      }
    }
    if (!ok)
      puts("impossible");
    else
      for(int i=0; i<r; i++)
        puts(g[i]);
    puts("----------");
  }
  return 0;
}
