#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


int matrix[3][3];
void umin(int*a, int b){
    if (b < *a)
       *a = b;
}
void inp() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            scanf("%d", &matrix[i][j]);
}
void solve() {
    int ans = INT_MAX;
    for (int f = 0; f < 3; ++f) {
        for (int s = 0; s < 3; ++s) {
            for (int th = 0; th < 3; ++th) {
                umin(&ans, matrix[0][f] + matrix[1][s] + matrix[2][th]);
            }
        }
    }
    printf("%d", ans);
}
int main(){
    inp();
    solve();
    puts("");
}
