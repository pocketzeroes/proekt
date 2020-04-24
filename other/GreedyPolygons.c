#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
    ll i, j, k;
    ll shapes;
    scanf("%lld", &shapes);
    double sides, length, expands, expandLength;
    for(i=0; i<shapes; i++){
        scanf("%lf %lf %lf %lf", &sides, &length, &expands, &expandLength);
        double basePolygon         = ((sides * length * length)) / (4 * tan(M_PI / sides));
        double addedRectangles     = sides * length * expands * expandLength;
        double addedPartialCircles = ((180 - (sides - 2) * 180.0 / sides) / 360.0) * M_PI * pow((expands * expandLength), 2)*sides;
        printf("%.10lf\n", basePolygon+addedRectangles+addedPartialCircles);
    }
    return 0;
}
