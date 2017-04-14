#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int p, diff, x, met = 0;
    for (p = 1; !met; p = p * 2) {
        if (p != 1) {
            puts("R A");fflush(stdout);
            puts("R B");fflush(stdout);
        }
        int moves = p;
        for (int i = 0; i < p; ++ i) {
            puts("F A");fflush(stdout);
            scanf("%d", &x);
            if (!x) {
                moves = i;
                break;
            }
        }
        for (int i = 0; i <= 2 * p; ++ i) {
            puts("E");fflush(stdout);
            scanf("%d", &x);
            if (x) {
                met = true;
                diff = moves - i;
                break;
            }
            puts("F B");fflush(stdout);
            scanf("%d", &x);
            if (!x)
                break;
        }
    }
    if (diff == p / 2) {
        printf("A %d\n", diff);fflush(stdout);
        return 0;
    }
    puts( "R A");fflush(stdout);
    puts( "R B");fflush(stdout);
    if (diff < 0) {
        diff = -diff;
        for (int i = 1; i <= diff; ++ i) {
            puts( "F B");fflush(stdout);
            scanf("%d", &x);
        }
    } 
    else {
        for (int i = 1; i <= diff; ++ i) {
            puts( "F A" );fflush(stdout);
            scanf("%d", &x);
        }
    }
    puts( "E");fflush(stdout);
    scanf("%d", &x);
    int cnt = 0;
    while (!x) {
        cnt += 1;
        puts( "F A" );fflush(stdout);
        scanf("%d", &x);
        puts( "F B");fflush(stdout);
        scanf("%d", &x);
        puts( "E");fflush(stdout);
        scanf("%d", &x);
    }
    printf("A %d\n", 2 * cnt + diff);fflush(stdout);
    return 0;
}





























































