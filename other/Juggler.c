#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAXN = 100100};
int perm    [MAXN]; 
int position[MAXN];
int bitdata [MAXN];

int bitquery(int i) {
    int res = 0;
    for (i += 2; i > 0; i -= i & -i)
        res += bitdata[i];
    return res;
}
void bitadd(int i) {
    for (i += 2; i < MAXN; i += i & -i)
        bitdata[i]++;
}
int query(int i) {
    return i + 1 - bitquery(i);
}
int main(){
    int n;
    while(scanf("%d", &n) && n){
        memset(bitdata, 0, sizeof(bitdata));
        for (int i = 0; i < n; i++){
            scanf("%d", &perm[i]);
            perm[i]--;
            position[perm[i]] = i;
        }
        int curpos = 0;
        int rem = n;
        long long totans = 0;
        bool scanfor = false;
        for (int i = 0; i < n; i++) {
            int targpos = position[i];
            int distfor = query(targpos) - query(curpos);
            if (scanfor) 
                distfor--;
            distfor = (distfor + rem) % rem; 
            int distback = rem - distfor;
            totans += min(distfor, distback) + 1;
            bitadd(targpos);
            rem--;
            curpos = targpos;
            scanfor = true;
        }
        printf("%lld\n", totans);
        break;
    }
    return 0;
}
