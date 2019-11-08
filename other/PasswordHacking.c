#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}

int main(){
    int n;
    scanf("%d", &n);
    double probabilities[n];
    for(int i=0; i<n; i++){
        getstr();
        scanf("%lf", &probabilities[i]);
    }
    qsort(probabilities, n, sizeof(double), cmpDbl);
    double expectedValue = 0.0;
    for(int i=0; i<n; i++)
        expectedValue += (i + 1) * probabilities[n - 1 - i];
    printf("%lf\n", expectedValue);
    return 0;
}
