#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ kMaxN =(int) 500+1}; 
enum{ kMod  =(int) 1e9+7};

int dp[kMaxN][kMaxN];


int Mod(int*a){
    if (*a >= kMod) {
        (*a) -= kMod;
        return Mod(a);
    }
    else if (*a < 0) {
        (*a) += kMod;
        return Mod(a);
    }
    else {
        return *a;
    }
}
int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    dp[0][0] = 1;
    for (int num_nodes = 1; num_nodes <= n; num_nodes += 1) {
        for (int first_child_num_nodes = 0; first_child_num_nodes < num_nodes; first_child_num_nodes += 1) {
            int second_child_num_nodes = num_nodes - first_child_num_nodes - 1;
            int first_child_sum = 0;
            int second_child_sum = 0;
            for (int height = 1; height <= min(max(first_child_num_nodes, second_child_num_nodes) + 1, h); height += 1) {
                first_child_sum += dp[first_child_num_nodes][height - 1];
                Mod(&first_child_sum);
                second_child_sum += dp[second_child_num_nodes][height - 1];
                Mod(&second_child_sum);
                dp[num_nodes][height] +=
                    (1LL * dp[first_child_num_nodes][height - 1] * second_child_sum +
                     1LL * dp[second_child_num_nodes][height - 1] * first_child_sum -
                     1LL * dp[first_child_num_nodes][height - 1] * dp[second_child_num_nodes][height - 1]) %
                    kMod;
                Mod(&dp[num_nodes][height]);
            }
        }
    }
    printf("%d\n", dp[n][h] );
    return 0;
}
