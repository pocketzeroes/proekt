#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


enum{ kMaxN = 20};

double arrival[1 << kMaxN];
double here[1 << kMaxN];

int main() {
    int n; 
    scanf("%d", &n);
    int weight[n];
    for(int i=0;i<n;i++) {
        scanf("%d", &weight[i]);
    }
    int total_sum = 0;
    for(int i=0;i<n;i++) {int itr=weight[i];
        total_sum += itr;
    }
    here[0] = 1.0;
    for (int conf = 0; conf < (1 << n); conf += 1) {
        int now_sum = 0;
        for (int i = 0; i < n; i += 1) {
            if (conf & (1 << i)) {
                now_sum += weight[i];
            }
        }
        double chx = 1.0 * now_sum / total_sum;
        double time_spent_here = chx / (1.0 - chx);
        double finish_time = arrival[conf] + (time_spent_here + 1.0) * here[conf];
        int remaining_sum = total_sum - now_sum;
        for (int i = 0; i < n; i += 1) {
            if (conf & (1 << i)) {
            } else {
                arrival[conf | (1 << i)] += finish_time * (weight[i]) / remaining_sum;
                here[conf | (1 << i)] += here[conf] * (weight[i]) / remaining_sum;
            }
        }
    }
    printf("%f\n", arrival[(1 << n) - 1]);
    return 0;
}
