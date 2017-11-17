#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    int n;
    scanf("%d", &n);
    double distance = y;
    for(int i = 0; i<n; ++i){
        int l, u; 
        double f;
        scanf("%d %d %lf", &l, &u, &f);
        distance -= u - l;
        distance += (u - l) * f;
    }
    printf("%.9lf\n", x / distance);
}
