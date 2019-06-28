#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ nmax = 100000};
int Neighbour[nmax+1][4];
bool Seen    [nmax+1][2];

int main(){
    int runs, run, n, g, i, j, k, p;
    bool passedgoal;
    scanf("%d", &runs);
    for (run = 0; run < runs; run++){
        scanf("%d %d ", &n, &g);
        for (i = 1; i <= n; i++)
            for (j = 0; j < 4; j++)
                scanf("%d", &Neighbour[i][j]);
        p = 0;
        memset(Seen, false, sizeof(Seen));
        for (i = 1; i <= n; i++)
            for (j = 0; j < 2; j++)
                if (!Seen[i][j]){
                    passedgoal = false;
                    while (!Seen[i][j&1]){
                        Seen[i][j&1] = true;
                        if (i == g)
                            passedgoal = true;
                        k = Neighbour[i][j];
                        for (j = 0; j < 4 && Neighbour[k][j] != i; j++);
                        if (j == 4){
                            fprintf(stderr, "Something is wrong!\n");
                            return 0;
                        }
                        i = k;
                        j ^= 2;
                    }
                    if (!passedgoal)
                        p++;
                }
        printf("%d\n", p);
    }
    return 0;
}
