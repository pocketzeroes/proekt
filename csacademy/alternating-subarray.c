#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int main() {
    
    int n, last, last_sign, current, length = 1, max_length = 0;
    scanf("%d", &n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &current);
        if (i > 1){
            if (current == last) 
                length = 1;
            else if (last_sign == (last < current))
                length = 2;
            else 
                length++;
            last_sign = last < current;
        }
        last = current;
        max_length = max(max_length, length);
    }
    printf("%d", max_length);
    return 0;
}
