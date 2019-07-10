#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int n;
ll x[100100], y[100100];

inline bool areCollinear(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
  return (x1*y2 + x2*y3 + x3*y1 == x1*y3 + x2*y1 + x3*y2);
}
bool tryit(int r1, int r2){
  if (r1 == r2)
    return false;
  bool done[100100];
  int notdone1 = -1;
  int notdone2 = -1;
  for (int i = 0; i < n; i++) {
    if (areCollinear(x[r1], y[r1], x[r2], y[r2], x[i], y[i]))
      done[i] = true;
    else {
      done[i] = false;
      if (notdone1 == -1)
        notdone1 = i;
      else if (notdone2 == -1)
        notdone2 = i;
    }
  }
  if (notdone2 == -1)
    return true;
  for (int i = 0; i < n; i++) {
    if (areCollinear(x[notdone1], y[notdone1], x[notdone2], y[notdone2], x[i], y[i]))
      done[i] = true;
    if (!(done[i]))
      return false;
  }
  return true;  
}
int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    scanf("%lld %lld", &x[i], &y[i]);
  for(int i=0; i<100; i++){
    if(tryit(rand() % n, rand() % n)){
      puts("success");
      return 0;
    }
  }
  puts("failure");
  return 0;
}

