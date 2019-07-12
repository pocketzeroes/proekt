#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int k, n, m;
  scanf("%d%d%d", &k, &n, &m);
  int supply[k][n]; memset(supply, 0,sizeof(supply));
  int demand[k][n]; memset(demand, 0,sizeof(demand));
  for(int i=0; i<m; ++i){
    int from, to, day, cap;
    scanf("%d%d%d%d", &from, &to, &day, &cap);
    --from, --to, --day;
    demand[from][day] += cap;
    if(day + 1 < n)
      supply[to][day + 1] += cap;
  }
  for(int i = 0; i < k * n; ++i){
    int airport, day, num_people;
    scanf("%d%d%d", &airport, &day, &num_people);
    --airport, --day;
    supply[airport][day] += num_people;
  }
  bool optimal = true;
  for(int i = 0; i < k; ++i){
    int net = 0;
    for(int j = 0; j < n; ++j){
      net += supply[i][j];
      if(net < demand[i][j])
        optimal = false;
      net -= demand[i][j];
    }
  }
  puts(optimal ? "optimal" : "suboptimal");
  return 0;
}
