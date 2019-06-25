#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp_int(const void *a, const void *b){
  return (*(int*)a-*(int*)b);
}
int main(){
  int cars, p, i, min_dist;
  int distance[100000];
  scanf("%d %d", &cars, &p);
  for(i=0;i<cars;i++){
    scanf("%d", &distance[i]);
  }
  qsort(distance, i, sizeof(int), comp_int);
  min_dist=p;
  for(i=1;i<cars;i++){
    if(min_dist-distance[0]+distance[i]<p*(i+1)){
      min_dist=p*(i+1)-distance[i]+distance[0];
    }
  }
  printf("%d\n", min_dist);
  return 0;
}
