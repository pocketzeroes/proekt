#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ __MAX_SZ = 1 << 18};
int ta[__MAX_SZ];
int max_win = 0;
int delta;
enum{ MX = 200500};
int ga[MX];

void init(int n){
    max_win = 0;
    delta = 1 << n;
    for(int i = delta; i < 2 * delta; i++)
        ta[i] = 1;
    for(int i = delta - 1; i > 0; i--)
        ta[i] = ta[2 * i] + ta[2 * i + 1];
}
void add(int pos){
    pos += delta;
    int level = 0;
    while(pos){
        ta[pos]--;
        if(ta[pos] <= 1)
            max_win = max(max_win, level);
        pos >>= 1;
        level++;
    }
}
int solve(){
    int z;
    scanf("%d", &z);
    init(z);
    int n = 1 << z;
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        x--;
        ga[x] = i;
    }
    for(int i = 0; i < n; i++){
        printf("%d ", max_win);
        add(ga[i]);
    }
    puts("");
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--)
        solve();
    return 0;
}
