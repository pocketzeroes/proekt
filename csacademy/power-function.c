#include <stdio.h>
#include<math.h>
#include<stdbool.h>

double power(double X, int Y) {
    double ans=1;
    bool sign=(Y>=0);
    Y=abs(Y);
    for(int i=0;i<31;i++)
    {
        if(Y&(1<<i))
            ans*=X;
        X*=X;
        
    }
    if(sign==true)
    return ans;
    else return 1/ans;
}

int main() {
    double X, Y;
    scanf("%lf %lf", &X, &Y);
    
    printf("%lf\n", power(X, Y) );
    return 0;
}
