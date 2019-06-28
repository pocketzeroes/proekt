#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ nmax = 16};
enum{ tmax = 3600};
int B[nmax];
int BFS[tmax+1], Presses[tmax+1];
bool Seen[tmax+1];

int main(){
    int runs, run, n, t, i, k, k2, cur, last;
    scanf("%d", &runs);
    for (run = 0; run < runs; run++){
        scanf("%d %d", &n, &t);
        for (i = 0; i < n; i++)
            scanf("%d", &B[i]);
        memset(Seen, false, sizeof(Seen));
        Seen[0] = true;
        BFS[0] = 0;
        Presses[0] = 0;
        last = 1;
        for (cur = 0; cur < last; cur++){
            k = BFS[cur];
            for (i = 0; i < n; i++){
                k2 = min(tmax, max(0, k+B[i]));
                if (!Seen[k2]){
                    Seen[k2] = true;
                    Presses[k2] = Presses[k] + 1;
                    BFS[last++] = k2;
                }
            }
        }
        for (k = t; !Seen[k]; k++);
        printf("%d %d\n", Presses[k], k-t);
    }
    return 0;
}
