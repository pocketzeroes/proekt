#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ kMaxN =(int) 1e5+1};
const int white = 0, black = 1;
int n;
int marbles[kMaxN];
int marbles_sum[kMaxN];

void Init() {
    for (int i = 1; i <= n; i += 1) {
        marbles_sum[i] = marbles_sum[i - 1] + marbles[i];
    }
}
int HowMany(int left, int length, int kind) {
    if (kind == black) {
        return marbles_sum[left + length - 1] - marbles_sum[left - 1];
    } else {
        return length - (marbles_sum[left + length - 1] - marbles_sum[left - 1]);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i += 1) {
        scanf("%d", &marbles[i]);
    }
    Init();
    int answer = n;
    int num_white = HowMany(1, n, white);
    int num_black = n - num_white;
    for (int i = 1; i + num_white - 1 <= n; i += 1) {
        int num_swaps = HowMany(i, num_white, black);
        answer = min(answer, num_swaps);
    }
    for (int i = 1; i + num_black - 1 <= n; i += 1) {
        int num_swaps = HowMany(i, num_black, white);
        answer = min(answer, num_swaps);
    }
    printf("%d\n", answer);
    return 0;
}
