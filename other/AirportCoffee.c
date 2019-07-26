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
double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

double totalLength;
double slowSpeed, 
       fastSpeed;
double waitTime, 
       drinkTime;
double oneCoffee;
int    n;
double*carts;
double*minimumTime;

double calcTime(int curPos, int nextPos){
    double distance = carts[nextPos]-carts[curPos];
    double time = minimumTime[nextPos];
    if (waitTime*slowSpeed >= distance)
        time += distance/slowSpeed;
    else {
        time += waitTime;
        distance -= waitTime*slowSpeed;
        if (drinkTime*fastSpeed >= distance)
            time += distance/fastSpeed;
        else {
            time += drinkTime;
            distance -= drinkTime*fastSpeed;
            time += distance/slowSpeed;
        }
    }
    return time;
}
int main(){
    totalLength = in_nextDouble();
    slowSpeed   = in_nextDouble();
    fastSpeed   = in_nextDouble();
    waitTime    = in_nextDouble();
    drinkTime   = in_nextDouble();
    oneCoffee   = waitTime*slowSpeed+drinkTime*fastSpeed;
    n           = in_nextInt();
    carts       = calloc(n+1, sizeof(double));
    for (int i = 0; i < n; i++)
        carts[i] = in_nextDouble();
    carts[n]    = totalLength;
    minimumTime = calloc(n+1, sizeof(double));
    int nextCart[n+1]; memset(nextCart, 0, sizeof(nextCart));
    for (int i = n-1; i >= 0; i--){
        minimumTime[i] = (totalLength-carts[i])/slowSpeed;
        nextCart   [i] = n;
        int k = i+1;
        for (int b = n; b >= 1; b /= 2){
            while (k+b <= n && carts[k+b]-carts[i] <= oneCoffee)
                k += b;
        }
        for (int j = k; j <= n && j <= k+1; j++){
            double time = calcTime(i,j);
            if (time < minimumTime[i]){
                minimumTime[i] = time;
                nextCart   [i] = j;
            }
        }
    }
    int count = 0;
    int pos   = 0;
    while (pos < n){
        count++;
        pos = nextCart[pos];
    }
    printf("%d\n", count);
    pos = 0;
    while(pos < n){
        printf("%d ", pos);
        pos = nextCart[pos];
    }
    puts("");
    return 0;
}
