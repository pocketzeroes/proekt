#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int get(int n){
    int res = 0;
    while (n /= 5) 
        res += n;
    return res;
}
int main(){
    int t;
    int X = 0;
{   int lb = 0, ub =(int) 1e6 + 1;
    while (ub - lb > 1){
        int m = (lb + ub) / 2;
        printf("Q %d\n", m); fflush(stdout);
        scanf("%d", &t);
        if (t)
            lb = m;
        else
            ub = m;
    }
    X = lb;  }
    int lb = -1, ub =(int) 1e5;
    while(ub - lb > 1){
        int m = (lb + ub) / 2;
        if(get(m) < X)
            lb = m;
        else
            ub = m;
    }
    printf("A %d\n", ub); fflush(stdout);
    return 0;
}

