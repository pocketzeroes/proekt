#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MaxN =(int) 1e5 + 15};
enum{ K = 200};
int  cnt [MaxN];
int* v   [MaxN];
int  vsz [MaxN];
bool used[MaxN];
int  g   [MaxN];
int n, k, q;


int cmp(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return (cnt[*a] < cnt[*b])?-1:1;
}
int main(){
    scanf("%d %d %d", &n, &k, &q);
    for(int i=1; i<=k; ++i){
        int ss;
        scanf("%d", &ss);
        v[i] = calloc(ss, sizeof(int));
        vsz[i] = ss;
        for(int z=0; z<ss; z++){
            scanf("%d", &v[i][z]);
            ++cnt[ v[i][z] ];
        }
    }
    for(int i=1; i<=k; ++i){
        qsort(v[i], vsz[i], sizeof(int), cmp);
        g[v[i][0]] = i;
    }
    for(int i=1; i<=q; ++i){
        int sz;
        scanf("%d", &sz);
        int ans = 0;
        int a[sz];
        memset(a, 0, sizeof(a));
        for(int z=0; z<sz; z++){
            scanf("%d", &a[z]);
            used[ a[z] ] = true;
        }
        for(int z=0; z<sz; z++){int x = a[z];
            if(cnt[x] == 1 && g[x] && vsz[g[x]] <= sz){
                int gg = g[x];
                bool OK = true;
                for(int w=0; w<vsz[gg];w++){int x = v[gg][w];
                    if(!used[x]){
                        OK = false;
                        break;
                    }
                }
                if(OK)
                    ++ans;
            }
        }
        for(int z=0; z<sz; z++){int x = a[z];
            used[x] = false;
        }
        printf("%d\n", ans);
    }
    return 0;
}
