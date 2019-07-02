#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N =   500}; 
enum{ S =   500}; 
enum{ M = 10000};

char Car[N][41];
int  P[N], Q[N], K[N];
char Spy[S][41];
int  Bill[S], CarTaken[S];
bool Consistent[S], Listed[S];


int main(){
  int cases, casenr, n, m, i, z, s, j, p, d;
  char Name[41], event;
  scanf("%d\n", &cases);
  for (casenr = 1; casenr <= cases; casenr++){ 
    scanf("%d %d\n", &n, &m);
    for (i = 0; i < n; i++)
      scanf("%s %d %d %d\n", Car[i], &P[i], &Q[i], &K[i]);
    z = 0;
    for (i = 0; i < m; i++){ 
      scanf("%*d %s %c\n", Name, &event);
      for (s = 0; s < z && strcmp(Name, Spy[s]) != 0; s++);
      if (s == z){
        strcpy(Spy[z++], Name);
        Bill[s] = 0;
        CarTaken[s] = -1;
        Consistent[s] = true;
      }
      switch (event){
        case 'p':
          if (CarTaken[s] >= 0)
            Consistent[s] = false;
          scanf("%s\n", Name);
          for (j = 0; j < n && strcmp(Name, Car[j]) != 0; j++);
          if (j == n){
            printf("Unknown car!\n");
            return 0;
          }
          CarTaken[s] = j;
          Bill[s] += Q[j];
          break;
        case 'a':
          if (CarTaken[s] < 0)
            Consistent[s] = false;
          scanf("%d\n", &p);
          Bill[s] += (p * P[CarTaken[s]] + 99) / 100;
          break;
        case 'r':
          if (CarTaken[s] < 0)
            Consistent[s] = false;
          scanf("%d\n", &d);
          Bill[s] += d * K[CarTaken[s]];
          CarTaken[s] = -1;
          break;
      }
    }
    for (i = 0; i < z; i++)
      Listed[i] = false;
    for (i = 0; i < z; i++){
      s = -1;
      for (j = 0; j < z; j++)
        if (!Listed[j] && (s == -1 || strcmp(Spy[j], Spy[s]) < 0))
          s = j;
      printf("%s ", Spy[s]);
      if (Consistent[s] && CarTaken[s] < 0)
        printf("%d\n", Bill[s]);
      else
        printf("INCONSISTENT\n");
      Listed[s] = true;
    }
  }
  return 0;
}
