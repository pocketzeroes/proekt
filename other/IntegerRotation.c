#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN =(int) 10e5+5};
int mp[MAXN];
int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        memset(mp,0,sizeof(mp));
        scanf("%d%d",&a,&b);
        int cnt = 0;
        for(int i = a; i<=b; ++i){
            int tmp = i;
            int p10 = 10;
            while(p10<=i)
                p10*=10;p10/=10;
            int k = log10(p10)+1;
            while(k--){
                tmp = (tmp%10)*p10+(tmp/10);
                if(tmp>i&&tmp<=b){
                    if(mp[tmp]==i)
                        continue;
                    mp[tmp] = i;
                    ++cnt;
                }
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
