#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll path[105];
ll ans [105];
ll pow_10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000 };
int anscnt = 0;

int getlen(ll x){
    int cnt = 0;
    while (x){
        cnt++;
        x /= 10;
    }
    return cnt;
}
void dfs(ll x, int cnt){
    if (x == 0 || x == 1){
        if (cnt<anscnt)
            return;
        else if (cnt>anscnt){
            anscnt = cnt;
            for (int i = 0; i<anscnt; i++)
                ans[i] = path[i];
        }
        else{
            int flag = 0;
            for (int i = 0; i<cnt; i++){
                if (path[i]<ans[i]){
                    flag = 1;
                    break;
                }
                else if(path[i] > ans[i]) 
                    break;
            }
            if (flag){
                for (int i = 0; i<anscnt; i++)
                    ans[i] = path[i];
            }
        }
        return;
    }
    int len = getlen(x);
    int end = (1LL << len) - 1;
    for (int i = end; i >= 0; i--){
        ll res = 0, cut = 0, resct = 0, cutct = 0;
        int flag = 0;
        for (int j = 0; j<len; j++){
            if ((i&(1 << j))>0){
                res = x / pow_10[j] % 10 * pow_10[resct++] + res;
                flag = 1;
            }
            else
                cut = x / pow_10[j] % 10 * pow_10[cutct++] + cut;
        }
        if (cut != 0 && cut != 1 && x%cut == 0 && getlen(cut) == cutct){
            if (res != 0 || res == 0 && flag == 1){
                path[cnt] = res;
                dfs(res, cnt + 1);
            }
            else
                dfs(res, cnt);
        }
    }
}
int main(){
    ll a;
    while(scanf("%lld", &a)==1 && a){
        anscnt = 0;
        dfs(a, 0);
        printf("%lld", a);
        for (int i = 0; i<anscnt; i++){
            printf(" %lld", ans[i]);
        }
        puts("");
    }
    return 0;
}
