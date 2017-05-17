#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef long long ll;

enum{ N   =(int) 1e5+10};
enum{ MOD =(int) 1e9+7 };
int a[N];
int32_t main()
{
    int n , x , X = 0;
    scanf("%d", &n);
    for(int i=0 ; i<n ; i++){
        scanf("%d", &a[i]);
        X ^= a[i];
    }
    if(X)
        return printf("%d\n", n) , 0;
    int mn = MOD;
    for(int i=0 ; i<n ; i++){
        if(a[i] > 0){
            mn = i+1;
            break;
        }
    }
    for(int i=n-1 ; i>=0 ; i--)
        if(a[i] > 0){
            mn = min(mn , n-i);
            break;
        }
    printf("%d\n", n - mn);
    return 0;
}
