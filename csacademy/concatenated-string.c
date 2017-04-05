#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_SZ 200000
typedef char* string;
typedef signed long long ll;
char Z[MAX_SZ];
char T[MAX_SZ];
int NS, NT;
int nex[201010][26];

void solve() {
    int i, j, k, l, r, x, y;
    scanf("%s", &Z);
    scanf("%s", &T);
    char*S;
    asprintf(&S, "%s%s",Z,Z);
    NS = strlen(S);
    NT = strlen(T);
    for (i = 0; i < 26; i++)
        nex[NS - 1][i] = 200010;
    for (i = NS - 2; i >= 0; i--){
        for (x = 0; x < 26; x++){
            nex[i][x] = nex[i + 1][x];
            if (S[i + 1] == x + 'a')
                nex[i][x] = i + 1;
        }
    }
    NS /= 2;
    ll cur = NS - 1;
    for(int i=0;T[i];i++){
        char c=T[i];
        if(nex[cur % NS][c - 'a'] > 200000)
            return (void)puts("-1");
        cur += nex[cur % NS][c - 'a'] - cur % NS;
    }
    printf("%lld\n", cur / NS);
}
int main(){
    solve();
    return 0;
}


