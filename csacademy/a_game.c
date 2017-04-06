#include<stdio.h>

int main() {
    int n; 
    scanf("%d", &n);
    int result = 0, num_a = 0, b_streak = 0;
    char c;
    while((c=getchar())!=EOF){
        if (c == 'B') 
            b_streak += 1;
        else {
            result ^= b_streak;
            b_streak = 0;
            num_a += 1;
        }
    }
    result ^= b_streak;
    if (num_a % 2 == 0) 
        puts("-1");
    else 
        puts(result != 0 ?"A":"B");
    return 0;
}
