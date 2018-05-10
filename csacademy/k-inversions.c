#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;

int main(){
    int n;
    ll  k;
    scanf("%d %lld", &n, &k);
    int p[n];
    memset(p, 0, sizeof(p));
    for(int i=0; i<n; i++){
        ll s = n-i-1;
        ll inv = s*(s-1)/2;
        if(inv < k){
            int j = k - inv;
            p[i] = j+1 + i;
            int x = n;
            for(int t=i+1;t<n;++t){
                if(p[i]==x) 
                    --x;
                p[t] = x;
                --x;
            }
            break;
        }
        else 
            p[i] = i+1;
    }
    for(int i=0; i<n; i++)
        printf("%d ", p[i]);
    puts("");
    return 0;
}
