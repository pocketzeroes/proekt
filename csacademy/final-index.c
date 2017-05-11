#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


int main() {
    int n, q, where;
    scanf("%d %d %d", &n, &q, &where);
    while (q--) {
        int op;
        scanf("%d", &op);
        int len; 
        scanf("%d", &len);
        int left, right;
void Reverse(){
    if (left <= where && where <= right){
        where = right + left - where;
    }
}
        if (op == 0) {
            left = 1;
            right = len;
        }
        else {
            right = n;
            left = right - len + 1;
        }
        Reverse(left, right, where);
    }
    printf("%d\n", where);
    return 0;
}
