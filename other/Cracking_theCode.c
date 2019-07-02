#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char M[100][1001], D[1001], X[1001];
char Decr[256], Encr[256], OverallEncr[256], OverallDecr[256];


int main(){
  int cases, casenr, n, m, i, j, k;
  char c, d;
  bool matchfound;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){ 
    scanf("%d\n", &n);
    for (i = 0; i < n; i++)
      scanf("%s\n", M[i]);
    scanf("%s\n%s\n", D, X);
    m = strlen(D);
    memset(OverallEncr, 0, 256);
    matchfound = false;
    for (i = 0; i < n; i++){ 
      if ((int)strlen(M[i]) != m)
        continue;
      memset(Decr, 0, 256);
      memset(Encr, 0, 256);
      for (j = 0; j < m; j++){
        if (Decr[M[i][j]] == 0) 
          Decr[M[i][j]] = D[j];
        else if (Decr[M[i][j]] != D[j]) 
          break;
        if (Encr[D[j]] == 0) 
          Encr[D[j]] = M[i][j];
        else if (Encr[D[j]] != M[i][j]) 
          break;
      }
      if (j < m) 
        continue;
      matchfound = true;
      for (c = 'a'; c <= 'z'; c++){
        if (OverallEncr[c] == 0)
          OverallEncr[c] = Encr[c];
        else if (OverallEncr[c] != Encr[c]) 
          OverallEncr[c] = '?';
      }
    }
    if (!matchfound){
      printf("IMPOSSIBLE\n");
      continue;
    }
    memset(OverallDecr, '?', 256);
    for (c = 'a'; c <= 'z'; c++)
      if (OverallEncr[c] >= 'a') 
        OverallDecr[OverallEncr[c]] = c;
    k = 0;
    for (c = 'a'; c <= 'z'; c++)
      if (OverallDecr[c] == '?')
        k++;
    if (k == 1){
      for (c = 'a'; OverallDecr[c] != '?'; c++); 
      for (d = 'a'; OverallEncr[d] >= 'a'; d++);
      OverallDecr[c] = d;
    }
    m = strlen(X);
    for (i = 0; i < m; i++)
      printf("%c", OverallDecr[X[i]]);
    printf("\n");
  }
  return 0;
}
