#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


typedef long long ll;
enum{ MAX =(int)2e5};

bool a[MAX];
int main(){
    ll n,x,y=0,z;
    scanf("%lld", &n);
    for(int i=0;i<n;i++){
        scanf("%lld", &x);
        if(x%2==0)
            z=(x/2)-1;
        else
            z=x/2;
        if(!a[z]){
            y++;
            a[z]=1;
        }
    }
    printf("%lld\n", y);
    return 0;
}
