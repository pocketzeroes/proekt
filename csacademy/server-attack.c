#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int main() {
    int n; 
    scanf("%d", &n);
    int last_bad_time = -1;
    int answer = 0;
    for (int i = 0; i < n; i += 1) {
        int person; 
        scanf("%d", &person);
        int time; 
        scanf("%d", &time);
        if (person == 2) {
            if (last_bad_time != -1) {
                answer += time - last_bad_time;
                last_bad_time = -1;
            }
        }
        else {
            if (last_bad_time == -1) {
                last_bad_time = time;
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}
