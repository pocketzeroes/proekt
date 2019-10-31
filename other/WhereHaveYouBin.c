#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ INF = 99999};
bool isAvailable[5];
int nBins,
    bestCost = INF,
    nPerOwner  [5],
    endCost    [5][150],
    bestEndCost[5][150];

void solve(int level){
  int spaceNeeded, c;
  if (level == 0){
    for (int o=0;o<5;o++){
      isAvailable[o] = false;
      for (int b=0;b<nBins;b++)
        bestEndCost[0][b] = endCost[o][b];
      solve(1);
      isAvailable[o] = true;
    }
  }
  else if (level == 5){
    for (int b=0;b<nBins;b++)
      if (bestEndCost[4][b] < bestCost)
        bestCost = bestEndCost[4][b];
  }
  else{
    for(int o=0;o<5;o++)
      if(isAvailable[o]){
        isAvailable[o] = false;
        spaceNeeded = 0;
        for (int o2=0;o2<5;o2++)
          if (!isAvailable[o2])
            spaceNeeded += nPerOwner[o2];
        for (int b=0;b<nBins;b++) {
          bestEndCost[level][b] = INF;
          if (b >= spaceNeeded - 1)
            for (int b2=0;b2<b-nPerOwner[o]+1;b2++) {
              c = bestEndCost[level-1][b2] + endCost[o][b];
              if (c < bestEndCost[level][b])
                bestEndCost[level][b] = c;
            }
        }
        solve(level+1);
        isAvailable[o] = true;
      }
  }
}
int main() {
  char bins[160],
    newBins[160];
  int nDeletes,
      d,
      c,
      costs[150],
      totalCost[5]={0};
  scanf("%s", &bins);
  nBins = strlen(bins);
  for(int i=0; i<nBins; i++)
    scanf("%d", &costs[i]);
  scanf("%d", &nDeletes);
  for(int i=0;i<nDeletes;i++){
    scanf("%d", &d);
    bins[d-1] = 'X';
    costs[d-1] = 0;
  }
  scanf("%s", newBins);
  for(int b=0;b<nBins;b++)
    for(int o=0;o<5;o++)
      if(bins[b] == "AEIOU"[o]){
        bins[b] = o;
        totalCost[o] += costs[b];
        nPerOwner[o]++;
      }
  for(int b=0;newBins[b]!=0;b++)
    for(int o=0;o<5;o++)
      if(newBins[b] == "AEIOU"[o])
        nPerOwner[o]++;
  for(int o=0;o<5;o++) {
    for(int i=0;i<nBins;i++)
      endCost[o][i] = INF;
    for(int e=0;e<nBins;e++)
      if(e >= nPerOwner[o] - 1){
        c = totalCost[o];
        for(int b=0;b<nPerOwner[o];b++)
          if(bins[e-b] == o)
            c -= costs[e-b];
        endCost[o][e] = c;
      }
  }
  for(int i=0; i<5; i++)
    isAvailable[i] = true;
  solve(0);
  printf("%d\n", bestCost);
  return 0;
}
