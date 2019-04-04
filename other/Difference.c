#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int a[12000];
bool used[200000000];
bool used2[400000000];
int unused_first = 1;

int main(){
    int m;
    scanf("%d %d", &a[0], &m);
    used [a[0]] = true;
    used2[a[0] + m] = true;
    int i;
    for (i = 1; !used[m] && !used2[a[i - 1]]; ++i){
        for (; used[unused_first]; ++unused_first);
        a[i] = a[i - 1] + unused_first;
        used[a[i]] = true;
        used2[a[i] + m] = true;
        for (int j = i - 1; j >= 0 && a[i] - a[j] < 40000; --j)
            used[a[i] - a[j]] = true;
    }
    printf("%d\n", i);
    return 0;
}
