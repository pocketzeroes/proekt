#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct Pair{
  char first;
  int second;
}Pair;
Pair newPair(char a, int b){
  Pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

int main() {
  int T, R, S, N;
  while(scanf("%d %d", &T, &R)==2){
    int tbp[T+1];memset(tbp,0,sizeof(tbp)); 
    int ts [T+1];memset(ts ,0,sizeof(ts )); 
    int tip[T+1];memset(tip,0,sizeof(tip)); 
    int rpc[R+1];memset(rpc,0,sizeof(rpc)); 
    int tdone[T+1];for(int i=0;i<T+1;i++)tdone[i]=-1;
    Pair*ti[T+1]; int tisize[T+1];
    for (int i = 1; i <= T; i++) {
      scanf("%d %d %d", &ts[i], &tbp[i], &N);
      ti[i]=(Pair*)malloc(N*sizeof(Pair)); tisize[i]=N;
      for (int j = 0; j < N; j++) {
        getchar();
        scanf("%c%d", &ti[i][j].first, &ti[i][j].second);
        if (ti[i][j].first == 'L') {
          rpc[ti[i][j].second] = max(rpc[ti[i][j].second], tbp[i]);
        }
      }
    }
    int held_by[R+1];
    memset(held_by,0,sizeof(held_by));
    for (int curtime = 0, ndone = 0; ndone < T;) {
      int curp[T+1];for(int i=0;i<T+1;i++)curp[i] = tbp[i];
      int bestp, besti, bestambig;
      bool change;
      do {
        change = false;
        bestp = 0;
        for (int i = 1; i <= T; i++)
        if (curtime >= ts[i] && tip[i] < tisize[i]) {
#define inst1 ti[i][tip[i]]
          bool blocked = false;
          if (inst1.first == 'L') {
            if (held_by[inst1.second]) {
              blocked = true;
              if (curp[held_by[inst1.second]] < curp[i]) {
                curp[held_by[inst1.second]] = curp[i];
                change = true;
              }
            }
            for (int j = 1; j <= R; j++) {
              if (held_by[j] && held_by[j] != i && rpc[j] >= curp[i]) {
                blocked = true;
                if (curp[held_by[j]] < curp[i]) {
                  curp[held_by[j]] = curp[i];
                  change = true;
                }
              }
            }
          }
          if (!blocked && curp[i] > bestp) {
            bestp = curp[i];
            besti = i;
            bestambig = false;
          } else if (!blocked && curp[i] == bestp) {
            bestambig = true;
          }
        }
      } while (change);

      if (bestp == 0) {curtime++; continue;}
      if (bestambig) puts("AMBIGUOUS!");

#define inst ti[besti][tip[besti]]
      if (inst.first == 'C' && inst.second > 0) {
        inst.second--;
        curtime++;
      } else {
        if (inst.first == 'L') {
          held_by[inst.second] = besti;
        } else if (inst.first == 'U') {
          held_by[inst.second] = 0;
        }
        if (++tip[besti] == tisize[besti]) {
          tdone[besti] = curtime;
          ndone++;
        }
      }
    }

    for (int i = 1; i <= T; i++) {
      printf("%d\n", tdone[i]);
    }
  }
  return 0;
}
























































