#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    double m, n;
    scanf("%lf %lf", &n, &m);
    int arr[110];
    for(int i=0; i<m; i++){
        scanf("%d", &arr[i]);
        if(i != 0)
            arr[i] += arr[i-1];
    }
    double ans = n/2.;
    for(int i=0; i<m; i++){
        if(ans<arr[i]){
            printf("%d\n", i+1);
            return 0;
        }
        else if(ans==arr[i]){
            puts("-1");
            return 0;
        }
    }
    return 0;
}
