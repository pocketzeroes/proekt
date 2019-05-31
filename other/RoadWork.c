#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum{ MAX_N = 1000};

int minInt(int a, int b){
  return (a < b ? a : b);
}
int maxInt(int a, int b){
  return (a > b ? a : b);
}
struct Car{
  int arrival;
  int lastLeave;
};

enum{ errTime = 0x3f3f3f3f};
struct Car toWest[MAX_N+1];
struct Car toEast[MAX_N+1];
int dpTimes[2][MAX_N+1][MAX_N+1][2];

int main(){
  int timeToPass, n;
  scanf("%d %d", &timeToPass, &n);
  int numToWest = 0;
  int numToEast = 0;
  for (int i = 0; i < n; ++i){
    char d[4];
    struct Car car;
    int arrivalTime, lastTimeToLeaveElseIrritated;
    scanf("%s %d %d", d, &car.arrival, &car.lastLeave);
    car.lastLeave += car.arrival;
    if (d[0] == 'W')
      toWest[numToWest++] = car;
    else
      toEast[numToEast++] = car;
  }
  toWest[numToWest].arrival = -1;
  toEast[numToEast].arrival = -1;
  memset(dpTimes[0], errTime, sizeof(dpTimes[0]));
  dpTimes[0][0][0][0] = dpTimes[0][0][0][1] = -3;
  int ret = -1;
  for (int numIrritated = 0; numIrritated <= n; ++numIrritated){
    int (*const curTimes)[MAX_N+1][2] = dpTimes[numIrritated % 2];
    int (*const nextTimes)[MAX_N+1][2] = dpTimes[(numIrritated+1) % 2];
    memset(nextTimes, errTime, sizeof(dpTimes[0]));
    for (int w = 0; w <= numToWest; ++w){
      for (int e = 0; e <= numToEast; ++e){
        for (int d = 0; d < 2; ++d){
          const struct Car *const carSame     = (d == 0 ? &toWest[w] : &toEast[e]);
          const struct Car *const carOpposite = (d == 1 ? &toWest[w] : &toEast[e]);
          if (carSame->arrival != -1){
            int curTime = curTimes[w][e][d];
            int newTime = maxInt(curTime+3, carSame->arrival);
            int (*const table)[MAX_N+1][2] = (newTime <= carSame->lastLeave ? curTimes : nextTimes);
            int *const ct = table[d == 0 ? w+1 : w][d == 1 ? e+1 : e];
            ct[d] = minInt(ct[d], newTime);
          }
          if (carOpposite->arrival != -1){
            int curTime = curTimes[w][e][d];
            int newTime = maxInt(curTime+timeToPass, carOpposite->arrival);
            int (*const table)[MAX_N+1][2] = (newTime <= carOpposite->lastLeave ? curTimes : nextTimes);
            int *const ct = table[d == 0 ? w : w+1][d == 1 ? e : e+1];
            ct[1-d] = minInt(ct[1-d], newTime);
          }
        }
      }
    }
    for (int d = 0; d < 2; ++d){
      if (curTimes[numToWest][numToEast][d] < errTime){
        ret = numIrritated;
        break;
      }
    }
    if (ret != -1)
      break;
  }
  printf("%d\n", ret);
  return 0;
}
