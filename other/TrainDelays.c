#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
typedef double dbl;
enum{ N = 1000};
char*Name[2*N];
int Origin[N], Dest[N], M[N], T[N], P[N], D[N];
dbl ETA[2*N][60];
dbl Processed[N];


void addstation(char*name, int*S){
  Name[*S] = strdup(name);
  for(int m = 0; m < 60; m++)
    ETA[*S][m] = 1e9;
  (*S)++;
}
int station_index(char*station, int*S){
  int i;
  for(i = 0; i < *S && strcmp(Name[i], station)!=0; i++);
    if(i == *S)
      addstation(station, S);
  return i;
}
int main(){
  int runs, run, n, S, i, j, k=0, m, s1, s2, s;
  dbl t, mintime;
  char station1[21], station2[21];
  runs = 1;
  for (run = 0; run < runs; run++){
    scanf("%s %s\n", station1, station2);
    S = 0;
    addstation(station1, &S);
    addstation(station2, &S);
    scanf("%d\n", &n);
    for (i = 0; i < n; i++){
      scanf("%s %s %d %d %d %d\n", station1, station2, &M[i], &T[i], &P[i], &D[i]);
      Origin[i] = s1 = station_index(station1, &S);
      Dest  [i] = s2 = station_index(station2, &S);
      Processed[i] = 1e9;
      if (s2 == 1)
        ETA[s1][M[i]] = min(ETA[s1][M[i]], (dbl)(T[i] + P[i]/100.0 * (D[i]+1)/2.0));
    }
    while(1){
      mintime = 1e9;
      for (i = 0; i < n; i++)
        if ((t = ETA[Origin[i]][M[i]]) < Processed[i] && t < mintime){
          mintime = t;
          k = i;
        }
      if (mintime == 1e9)
        break;
      Processed[k] = mintime;
      s = Origin[k];
      for (m = 0; m < 60; m++)
        ETA[s][m] = min(ETA[s][m], (60+M[k]-m)%60 + mintime);
      for (i = 0; i < n; i++)
        if (Dest[i] == s){
          t = 0;
          for (j = 0; j <= D[i]; j++)
            t += (j == 0 ? 1 - P[i]/100.0 : P[i]/100.0/D[i]) * (T[i]+j + ETA[s][(M[i]+T[i]+j)%60]);
          ETA[Origin[i]][M[i]] = min(ETA[Origin[i]][M[i]], t);
        }
    }
    mintime = 1e9;
    for (m = 0; m < 60; m++)
      mintime = min(mintime, ETA[0][m]);
    if (mintime < 1e9)
      printf("%.7lf\n", (double)mintime);
    else
      printf("IMPOSSIBLE\n");
  }
  return 0;
}
