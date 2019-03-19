#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    double g;
    scanf("%d %lf", &n, &g);
    double d [n], 
           th[n];
    for(int i=0; i<n; i++)
        scanf("%lf %lf", &d[i], &th[i]);
    double h[n+1]; memset(h, 0, sizeof(h));
    for(int i=n-1; i>=0; i--)
        h[i] = h[i+1] + d[i]*cos(th[i]*M_PI/180);
    for(int i=0; i<n; i++)
        printf("%.10lf\n", sqrt(2*g*h[i]) );
    return 0;
}
