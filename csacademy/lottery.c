#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ nmax = (int) 1e4    };
enum{ lim  = 100 + 1};
bool f   [nmax + 1];
int  ind [nmax + 1];
int  v   [nmax + 1];
int  qk  [lim  + 1];
int  rasp[lim  + 1][nmax + 1];

int main(){
    int n, l;
    scanf("%d %d", &n, &l);
    for(int i=1; i<=n; ++i)
        scanf("%d", &v[i]);
    int q;
    scanf("%d", &q);
    for(int i=1; i<=q; ++i){
        scanf("%d", &qk[i]);
        f[qk[i]] = 1;
    }
    int aux = 1;
    for(int i=1; i<=l; ++i){
        ind[i] = aux;
        aux += f[i];
    }
    for(int d=1; d+1<=n-l+1; ++d){
        int j = 1 + d, s = 0;
        for(int k=0; k<l-1; ++k){
            s += (v[1 + k] != v[j + k]);
        }
        for(int i=1; j<=n-l+1; ++i, ++j){
            s += (v[i + l - 1] != v[j + l - 1]);
            ++rasp[ind[s]][i];
            ++rasp[ind[s]][j];
            s -= (v[i] != v[j]);
        }
    }
    for(int i=1; i<=q; ++i)
        for(int j=1; j<=n-l+1; ++j)
            rasp[i][j] += rasp[i - 1][j];
    for(int j=1; j<=q; ++j){
        for(int i=1; i<=n-l+1; ++i)
            printf("%d ", rasp[ind[qk[j]]][i] );
        puts("");
    }
    return 0;
}
