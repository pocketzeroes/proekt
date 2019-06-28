#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

typedef long long ll;
int main(){
  int n = in_nextInt();
  int k = in_nextInt();
  int x[n];
  int t[n];
  for (int i = 0; i < n; i++){
    x[i] = in_nextInt();
    t[i] = in_nextInt();
  }
  ll total = 0;
  for(int i = 0; i < n && x[i] < 0; i++){
    if(t[i] > 0){
      int distPerTrip = x[i] * -2;
      int nFullTrips = t[i] / k;
      total += distPerTrip * nFullTrips;
      t[i] %= k;
      if(t[i] > 0){
        total += distPerTrip;
        int leftover = k - t[i];
        t[i] = 0;
        for(int j = i + 1; j < n && leftover > 0 && x[j] < 0; j++){
          int amountWhichCanBeUsed = min(leftover, t[j]);
          leftover -= amountWhichCanBeUsed;
          t[j]     -= amountWhichCanBeUsed;
        }
      }
    }
  }
  for(int i = n - 1; i >= 0 && x[i] > 0; i--){
    if(t[i] > 0){
      int distPerTrip = x[i] * 2;
      int nFullTrips  = t[i] / k;
      total += distPerTrip * nFullTrips;
      t[i] %= k;
      if(t[i] > 0){
        total += distPerTrip;
        int leftover = k - t[i];
        t[i] = 0;
        for(int j = i - 1; j >= 0 && leftover > 0 && x[j] > 0; j--){
          int amountWhichCanBeUsed = min(leftover, t[j]);
          leftover -= amountWhichCanBeUsed;
          t[j]     -= amountWhichCanBeUsed;
        }
      }
    }
  }
  printf("%lld\n", total);
  return 0;
}
