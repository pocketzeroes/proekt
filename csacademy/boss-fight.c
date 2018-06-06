#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int main(){
    ll a1, l1, a2, l2, c, x, y, i, j, k;
    scanf("%lld%lld%lld%lld%lld%lld%lld", &a1, &l1, &a2, &l2, &c, &x, &y);
    for(i=0;i<=c;i++){
        j=ceil((l1+(i*y))/(1.0*a2));
        k = ceil((1.0*l2)/(a1+((c-i)*x)));
        if(j>=k){
            printf("1");
            return 0;
        }
    }
    printf("0");
    return 0;
}
