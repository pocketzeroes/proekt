#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ VAL_MAX =(int) 1e6};
int N;
int best[VAL_MAX + 5][2];
int ans;

int main() {
    scanf("%d", &N);
    while (N--) {
      int x;
      scanf("%d", &x);
      ++x;
      ans = max(ans, (best[x][0] = best[x - 1][0] + 1) + 1);
      ans = max(ans, best[x][1] = max(best[x - 1][1] + 1, best[x - 2][0] + 2));
    }
    printf("%d", ans);
    return 0;
}
