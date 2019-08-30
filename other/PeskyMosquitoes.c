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

typedef struct{
    double x, y;
}pt;
pt newpt(double x, double y){
    return(pt){x,y};
}

double distanceBetweenPoints(pt p1, pt p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
pt centerOfCircle(pt p1, pt p2, double radius){
    pt midpoint = newpt((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    double lengthP1ToMidpoint = distanceBetweenPoints(p1, midpoint);
    double lengthMidToCenter = sqrt(pow(radius, 2) - pow(lengthP1ToMidpoint, 2));
    double radians = atan2(p1.x - p2.x, p2.y - p1.y);
    pt centerOfCircle = newpt(lengthMidToCenter * cos(radians) + midpoint.x, lengthMidToCenter * sin(radians) + midpoint.y);
    return centerOfCircle;
}
int main(){
    int numTestCases = in_nextInt();
    while(numTestCases-- > 0){
        int numMosquitoes = in_nextInt();
        double radius     = in_nextDouble()/2.0;
        pt mosquitoes[numMosquitoes];
        for(int i=0; i<numMosquitoes; i++){
            double x = in_nextDouble();
            double y = in_nextDouble();
            mosquitoes[i] = newpt(x, y);
        }
        int bestCatch = 0;
        for(int i=0; i<numMosquitoes; i++){
            for(int j=0; j<numMosquitoes; j++){
                int caughtMosquitoes = 0;
                pt center = centerOfCircle(mosquitoes[i], mosquitoes[j], radius);
                for(int k=0; k<numMosquitoes; k++){
                    double pointsDistance = sqrt(pow(center.x - mosquitoes[k].x, 2) + pow(center.y - mosquitoes[k].y, 2));
                    if (pointsDistance <= radius)
                        caughtMosquitoes++;
                }
                if (caughtMosquitoes > bestCatch)
                    bestCatch = caughtMosquitoes;
            }
        }
        printf("%d\n", bestCatch);
    }
    return 0;
}
