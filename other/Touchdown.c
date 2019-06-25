#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
  int numPlays = in_nextInt();
  int down = 1;
  int yardsToFirst = 10;
  int totalYardsGained = 0;
  bool didntGetFirst = false;
  bool safety = false;
  for(int i = 0; i < numPlays; i ++){
    int currentPlay = in_nextInt();
    totalYardsGained += currentPlay;
    yardsToFirst -= currentPlay;
    if(totalYardsGained >= 80)
      break;
    if(totalYardsGained <= -20){
      safety = true;
      break;
    }
    if(yardsToFirst > 0 && down == 4){
      didntGetFirst = true;
      break;
    }
    else if (yardsToFirst > 0)
      down ++;
    else{
      yardsToFirst = 10;
      down = 1;
    }
  }
  if (totalYardsGained >= 80 && !didntGetFirst)
    puts("Touchdown");
  else if(safety)
    puts("Safety");
  else
    puts("Nothing");
  return 0;
}
