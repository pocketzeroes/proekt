#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int cases;
  scanf("%d", &cases);
  for(int i = 0; i < cases; ++i){
    int n_scores;
    scanf("%d", &n_scores);
    int scores[n_scores];
    int sum = 0;
    for(int i = 0; i < n_scores; ++i){
      scanf("%d", &scores[i]);
      sum += scores[i];
    }
    double average = (double) sum / n_scores;
    int above_avg = 0;
    for(int i = 0; i < n_scores; ++i)
      if(scores[i] > average)
        above_avg++;
    printf("%.3lf%%\n", (double) above_avg / n_scores * 100);
  }
	return 0;
}
