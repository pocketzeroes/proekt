#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

typedef long long ll;

ll m, n, kei;
ll aa[100010];

void maxset(int*to, int val){ 
   *to = max(*to, val);
}
int main(){
    scanf("%lld", &n);
    for(int i=0;i<n;i++)
        scanf("%lld", &aa[i]);
    int best      = 0;
    int upcount   = 1;
    int downcount = 1;
    ll  last      = aa[0];
    for(int i=(1);(i)!=(n);++(i)){
        if (last <= aa[i])
            upcount++;
        else
            upcount = 1;
        if (last >= aa[i])
            downcount++;
        else
            downcount = 1;
        maxset(&best, max(upcount, downcount));
        last = aa[i];
    }
    printf("%d\n", best);
    return 0;
}







