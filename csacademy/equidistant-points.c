#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

double asmSqrt(double x) {
  __asm__ ("fsqrt" : "+t" (x));
  return x;
}
int nxt(){
    int aaa;
    scanf("%d",&aaa);
    return aaa;
}
int main(){
    int n=nxt();
    puts("0 1");
    puts("1 1");
    puts("0.5 0.1339745962155614");
    double x=0.5;
    double y=0.1339745962155614;
    n-=3;
    while(n--){
        y+=0.00012;
        double temp=1.0-y;
        temp*=temp;
        temp=1.0-temp;
        temp = asmSqrt(temp);
        x=temp;
        printf("%0.10lf %0.10lf\n",x,y);
    }
    return 0;
}

























