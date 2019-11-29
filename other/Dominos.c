#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum{ N = 1100000};

char toppled[N];
int edges[N][2];
unsigned se[N];
char incoming[N];
char seen[N];
int nextfin;
int finish[N];
int nums[N];

int topple(int x) {
    if(!toppled[x]) {
        int i;
        toppled[x] = 1;
        for(i = se[x]; i < N && edges[i][0] == x; i++) {
            topple(edges[i][1]);
        }
    }
}
int comp(const void*a, const void*b){
   return ( *(int*)a - *(int*)b );
}
int dfs(int n) {
    if(!seen[n]) {
        int i;
        seen[n] = 1;
        for(i = se[n]; i < N && edges[i][0] == n; i++) {
            dfs(edges[i][1]);
        }
        finish[n] = ++nextfin;
    }
}
int fincomp(const void*pa, const void*pb){
    int*e1=(int*)pa;
    int*e2=(int*)pb;
    return finish[*e2] - finish[*e1];
}
int main() {
    int CASES;
    scanf("%d", &CASES);
    while(CASES--) {
        int n, m, i, cnt;
        memset(toppled,0,sizeof(toppled));
        memset(incoming,0,sizeof(incoming));
        memset(seen,0,sizeof(seen));
        memset(finish,0,sizeof(finish));
        scanf("%d %d", &n, &m);
        for(i=0; i<m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            edges[i][0] = x;
            edges[i][1] = y;
            incoming[y] = 1;
        }
        qsort(edges, m, sizeof(edges[0]), comp);
        memset(se,-1,sizeof(se));
        for(i=m-1; i>=0; i--) {
            se[edges[i][0]] = i;
        }
        cnt = 0;
        for(i=0; i<n; i++) dfs(i);
        for(i=0; i<n; i++) nums[i] = i;
        qsort(nums, n, sizeof(nums[0]), fincomp);
        for(i=0; i<n; i++) {
            if(!toppled[nums[i]]) {
                cnt++;
                topple(nums[i]);
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
